#ifndef FSM_H
#define FSM_H

#include <string>
#define SIG_FAULT -1
#define SIG_SUCCESS 0

class fsmFileMask {
private:
	std::string mask;
	struct state {
		int n;
		char label;
		bool isFinal;
		state() {}
		state(int _n, char _label, bool _isFinal):
			 n(_n), label(_label), isFinal(_isFinal) {
		
		}
	} *states;
	int states_size;
	state* cur;
		
	state* nextState() {
		return &(this->states[this->cur->n + 1]);
	}
	void jump(state* s) {
		this->cur = s;
	}
	void jump() {
		this->cur = this->nextState();
	}
public:
	fsmFileMask(std::string mask_) {
		this->mask = mask_;
		this->states_size = mask.size() + 1;
		this->states = new fsmFileMask::state[this->states_size];
		for (int i=0; i<mask.size(); i++) 
			this->states[i] = fsmFileMask::state(i, mask[i], false);
			
		this->states[mask.size()] = fsmFileMask::state(mask.size(), '\0', true);
		this->cur = &(this->states[0]);
	}
	~fsmFileMask() {
		delete[] this->states;
	}
	int recognize(std::string str) {
		int size = str.size();
		for (int i = 0; i<size; i++) {
			char cur = str[i];
			if (cur == this->cur->label) {
				this->jump();
				continue;
			}
			if (this->cur->label == '*') {
				if ((i == size-1) || (str[i+1] == this->nextState()->label)) {
					this->jump();
				}
				else {
					continue;
				}
			}
			else if (this->cur->label == '?') {
				this->jump();
			}
			else {
				return SIG_FAULT;
			}
			
		}
		if (this->cur->isFinal)
			return SIG_SUCCESS;
		return SIG_FAULT;
	}
};

#endif
