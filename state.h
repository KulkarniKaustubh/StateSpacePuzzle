#ifndef STATE_H
#define STATE_H

struct jug
{
	int lim;
	int rem;
};

typedef struct jug jug;

struct state
{
	jug A;
	jug B;
	jug C;
	int fn_index;
};

typedef struct state state_t;

void set_state(state_t* ptr_state, int lim1, int lim2, int lim3, int init_rem1, int init_rem2, int init_rem3);
void disp_state(const state_t* ptr_state);

void moveAB(const state_t* src, state_t *dst);
void moveAC(const state_t* src, state_t *dst);
void moveBA(const state_t* src, state_t *dst);
void moveBC(const state_t* src, state_t *dst);
void moveCA(const state_t* src, state_t *dst);
void moveCB(const state_t* src, state_t *dst);

int are_same(const state_t* lhs, const state_t* rhs);
int is_valid(const state_t* ptr_state);
#endif
