#include <stdio.h>
#include "list.h"

#define DEBUG 1
int main()
{
	state_t start;
	state_t goal;
	void (*move[])(const state_t*, state_t*) = {
		moveAB,
		moveAC,
		moveBA,
		moveBC,
		moveCA,
		moveCB,
	};

	int lim1, lim2, lim3;
	int init_rem1, init_rem2, init_rem3;
	int fin_rem1, fin_rem2, fin_rem3;
	scanf ("%d", &lim1);
	scanf ("%d", &lim2);
	scanf ("%d", &lim3);
	scanf ("%d", &init_rem1);
	scanf ("%d", &init_rem2);
	scanf ("%d", &init_rem3);
	scanf ("%d", &fin_rem1);
	scanf ("%d", &fin_rem2);
	scanf ("%d", &fin_rem3);

	int total = init_rem1 + init_rem2 + init_rem3;

	set_state(&start, lim1, lim2, lim3, init_rem1, init_rem2, init_rem3);
	set_state(&goal, lim1, lim2, lim3, fin_rem1, fin_rem2, fin_rem3);
	// disp_state (&start);
	// disp_state (&goal);

	list_t mylist;
	init_list(&mylist);
	add_at_end(&mylist, &start);
	int is_soln = 0;
	state_t temp;
	set_state (&temp, lim1, lim2, lim3, 0, 0, 0);
	int fn_index;
	int done = 0;
	int nos = 0;
	while(! is_soln)
	{
		fn_index = mylist.tail->st.fn_index;
		if(DEBUG)
		{
			// printf("trying transition %d on\n", fn_index);
			// disp_state(&mylist.tail->st);
		}
		if ( fn_index <= 5 ) {
			// set_state (&temp, lim1, lim2, lim3, 0, 0, 0);
			move[fn_index](&mylist.tail->st, &temp);
		}
		// printf ("Temporary print \n");
		// disp_state (&temp);
		// printf ("%d and %d\n",temp.fn_index, fn_index);
		if( is_valid (&mylist.tail->st, total) && is_valid(&temp, total) && ! is_repeated(&mylist, &temp))
		{
			if(DEBUG)
			{
				// printf("adding : ");
				// disp_state(&temp);
			}
			add_at_end(&mylist, &temp);
			is_soln = are_same(&temp, &goal);
		}
		else
		{
			// printf ("INSIDE ELSE\n");
			set_state (&temp, lim1, lim2, lim3, mylist.tail->st.A.rem, mylist.tail->st.B.rem, mylist.tail->st.C.rem);
			// temp.fn_index = mylist.tail->st.fn_index;
			// not checking for all solutions
			while( ++mylist.tail->st.fn_index >= 6 )
			{
				// printf ("INSIDE WHILE\n");
				if(DEBUG)
				{
					// printf("\n BACKTRACK : ");
					// disp_state(&mylist.tail->st);
					// printf ("NOS: %d \n", nos);
				}
				remove_at_end(&mylist);
				if (mylist.tail)
					set_state (&temp, lim1, lim2, lim3, mylist.tail->st.A.rem, mylist.tail->st.B.rem, mylist.tail->st.C.rem);
				else {
					done = 1;
					break;
				}
			}
		}
		if (is_soln) {
			++nos;
			disp_list (&mylist);
			printf ("\n");
			is_soln = 0;
			remove_at_end (&mylist);
			set_state (&temp, lim1, lim2, lim3, mylist.tail->st.A.rem, mylist.tail->st.B.rem, mylist.tail->st.C.rem);
			++mylist.tail->st.fn_index;
		}
		if (done == 1) break;
		// if (are_same (&temp, &start)) break;
	}
	printf ("%d\n", nos);
}
