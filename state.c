#include <stdio.h>
#include "state.h"

void set_state(state_t* ptr_state, int lim1, int lim2, int lim3, int rem1, int rem2, int rem3)
{
	ptr_state->A.lim = lim1;
	ptr_state->B.lim = lim2;
	ptr_state->C.lim = lim3;

	ptr_state->A.rem = rem1;
	ptr_state->B.rem = rem2;
	ptr_state->C.rem = rem3;

	ptr_state->fn_index = 0;
}

void disp_state(const state_t* ptr_state)
{
		printf("%d %d %d\n", ptr_state->A.rem, ptr_state->B.rem, ptr_state->C.rem);
}

void moveAB (const state_t* src, state_t* dst)
{
	if (src->A.rem == 0)
		return;
	if (src->B.lim == src->B.rem)
		return;

	if (src->A.rem + src->B.rem > src->B.lim)
	{
		dst->B.rem = dst->B.lim;
		dst->A.rem = src->A.rem + src->B.rem - dst->B.lim;
	}
	if (src->A.rem + src->B.rem == src->B.lim)
	{
		dst->B.rem = dst->B.lim;
		dst->A.rem = 0;
	}
	if (src->A.rem + src->B.rem < src->B.lim)
	{
		dst->B.rem = src->A.rem + src->B.rem;
		dst->A.rem = 0;
	}
	if (dst->A.rem < 0) dst->A.rem = 0;
}

void moveAC (const state_t* src, state_t* dst)
{
	if (src->A.rem == 0)
		return;
	if (src->C.lim == src->C.rem)
		return;

	if (src->A.rem + src->C.rem > src->C.lim)
	{
		dst->C.rem = dst->C.lim;
		dst->A.rem = src->A.rem + src->C.rem - dst->C.lim;
	}
	if (src->A.rem + src->C.rem == src->C.lim)
	{
		dst->C.rem = dst->C.lim;
		dst->A.rem = 0;
	}
	if (src->A.rem + src->C.rem < src->C.lim)
	{
		dst->C.rem = src->A.rem + src->C.rem;
		dst->A.rem = 0;
	}
	if (dst->A.rem < 0) dst->A.rem = 0;
}

void moveBA (const state_t* src, state_t* dst)
{
	if (src->B.rem == 0)
		return;
	if (src->A.lim == src->A.rem)
		return;

	if (src->B.rem + src->A.rem > src->A.lim)
	{
		dst->A.rem = dst->A.lim;
		dst->B.rem = src->B.rem + src->A.rem - dst->A.lim;
	}
	if (src->B.rem + src->A.rem == src->A.lim)
	{
		dst->A.rem = dst->A.lim;
		dst->B.rem = 0;
	}
	if (src->B.rem + src->A.rem < src->A.lim)
	{
		dst->A.rem = src->B.rem + src->A.rem;
		dst->B.rem = 0;
	}
	if (dst->B.rem < 0) dst->B.rem = 0;
}

void moveBC (const state_t* src, state_t* dst)
{
	if (src->B.rem == 0)
		return;
	if (src->C.lim == src->C.rem)
		return;

	if (src->B.rem + src->C.rem > src->C.lim)
	{
		dst->C.rem = dst->C.lim;
		dst->B.rem = src->B.rem + src->C.rem - dst->C.lim;
	}
	if (src->B.rem + src->C.rem == src->C.lim)
	{
		dst->C.rem = dst->C.lim;
		dst->B.rem = 0;
	}
	if (src->B.rem + src->C.rem < src->C.lim)
	{
		dst->C.rem = src->B.rem + src->C.rem;
		dst->B.rem = 0;
	}
	if (dst->B.rem < 0) dst->B.rem = 0;
}

void moveCA (const state_t* src, state_t* dst)
{
	if (src->C.rem == 0)
		return;
	if (src->A.lim == src->A.rem)
		return;

	if (src->C.rem + src->A.rem > src->A.lim)
	{
		dst->A.rem = dst->A.lim;
		dst->C.rem = src->C.rem + src->A.rem - dst->A.lim;
	}
	if (src->C.rem + src->A.rem == src->A.lim)
	{
		dst->A.rem = dst->A.lim;
		dst->C.rem = 0;
	}
	if (src->C.rem + src->A.rem < src->A.lim)
	{
		dst->A.rem = src->C.rem + src->A.rem;
		dst->C.rem = 0;
	}
	if (dst->C.rem < 0) dst->C.rem = 0;
}

void moveCB (const state_t* src, state_t* dst)
{
	if (src->C.rem == 0)
		return;
	if (src->B.lim == src->B.rem)
		return;

	if (src->C.rem + src->B.rem > src->B.lim)
	{
		dst->B.rem = dst->B.lim;
		dst->C.rem = src->C.rem + src->B.rem - dst->B.lim;
	}
	if (src->C.rem + src->B.rem == src->B.lim)
	{
		dst->B.rem = dst->B.lim;
		dst->C.rem = 0;
	}
	if (src->C.rem + src->B.rem < src->B.lim)
	{
		dst->B.rem = src->C.rem + src->B.rem;
		dst->C.rem = 0;
	}
	if (dst->C.rem < 0) dst->C.rem = 0;
}


int are_same(const state_t* lhs, const state_t* rhs)
{
	return lhs->A.rem == rhs->A.rem && lhs->B.rem == rhs->B.rem
		&& lhs->C.rem == rhs->C.rem;
}

int is_valid(const state_t* ptr_state)
{
	if (ptr_state->fn_index >= 6 || ptr_state->A.rem > ptr_state->A.lim || ptr_state->B.rem > ptr_state->B.lim || ptr_state->C.rem > ptr_state->C.lim ||
		ptr_state->A.rem < 0 || ptr_state->B.rem < 0 || ptr_state->C.rem < 0 )//|| (ptr_state->A.rem + ptr_state->B.rem + ptr_state->C.rem) != 8)
		return 0;
	return 1;
}
