/*
detector.c

Student Name : Keven Iskander
Student ID # : 160634540

*/

#include <string.h>
#include <stddef.h>
#include <stdio.h>

#define MAX_LINE_LENGTH 1000

/*
Any required standard libraries and your header files here
*/

void detector(FILE *fd){
    /*
        Your code here.
        You may edit the following code
    */
    char line_buffer[MAX_LINE_LENGTH];
    //int start_time, run_time, process_id, num_exchanges, exchange_time;
    char *token;
    
    int n, m, i = 0;

    //Processs first line
    fgets(line_buffer, MAX_LINE_LENGTH, fd);
    sscanf(line_buffer, "%d %d",&n, &m);
    //printf("%d %d", n, m);
    int request_array[n][m], allocation_array[n][m], unused_array[m];
    int sig = 0;
    int current;
    //while loop runs through the input text file and stores rows in resource_array, process_array and unused_arar
    while (fgets(line_buffer, MAX_LINE_LENGTH, fd) != NULL && line_buffer[0] != '\n'){
		int j = 0;
		token = strtok(line_buffer, " ");
		if (i == n) {
			//printf("\n------------------------");
			sig++;
			i = 0;
		}

		//printf("\n");
		while (token != NULL) {

			sscanf(token, "%d", &current);

			if (sig == 0) {
				//printf("\nResource Row: ");
				request_array[i][j] = current;
				//printf("%d%d: %d ", i, j, request_array[i][j]);
			} else if (sig == 1) {
				//printf("\nAllocation Row: ");
				allocation_array[i][j] = current;
				//printf("%d%d: %d ", i, j, allocation_array[i][j]);
			} else if (sig == 2) {
				//printf("\nUnused: ");
				unused_array[j] = current;
				//printf("%d%d: %d ", i, j, unused_array[j]);
			}

			token = strtok(NULL, " ");

			if (j == m) {
				j = 0;
			} else {
				j++;
			}
		}
		i++;
	}
	//Process remaining lines
	//Hint use template code from A1 to parse each line


	//Deadlock detection starts here

	int deadlock_detected = 0;
	int processed[n], finished[n], T[m], cleared[n], locked[n], terminated[n], term_counter = 0;
	int not_done, resets = 0, done = 0, c = 0, d = 0 ,e = 0, f = 0, h = 0, g = 0, k = 0, l = 0, p = 0, w = 0, x = 0, y = n-1, z = 0, finished_counter = 0, deadlock_counter = 0, t_counter = 0;


	for(l = 0; l < m; l++){
		T[l] = unused_array[l];

	}
	for(h = 0; h < n; h++){
		finished[h] = 0;
		cleared[h] = 0;
		locked[h] = 0;
		terminated[h] = 0;
	}
	for(w = 0; w < n; w++){
		finished_counter = 0;
		for(x = 0; x < m; x++){
			if(allocation_array[w][x]==0){
				finished_counter++;
			}
		}
		if(finished_counter == n){

			//finished[w] = 1;

		}
	}
	//printf("--------------------------------------\n");
	while(y >= 0 && done!=n){
		//deadlock_resolved = 1;
		//printf("LEVEL %d \n", y);

		if((finished[y] == 0)){
			//printf("jim\n");
		t_counter = 0;
			for(z = 0; z < m; z++){
				if(done<=n){
					//printf("                R: %d T: %d\n", request_array[y][z], T[z]);
					if(request_array[y][z]<=T[z]){

						//printf("t_counter %d\n",t_counter);
						t_counter++;

					}

				}
			}

			if(t_counter == m){
				finished[y] = 1;
				t_counter = 0;


				for(p = 0; p < m; p++){
					//printf(" TT %d \n", T[p]);
					T[p] += allocation_array[y][p];
					//printf(" TT %d \n", T[p]);

				}
			}

			t_counter = 0;
			//printf("TZ %d ra %d", T[z], request_array[y][z]);

			//printf("   Updated Finished: %d\n",finished[z]);


			if(finished[y]==1){

				done++;
				//printf("Updated Finished: %d %d\n",finished[y],y);
				cleared[e] = y;
				//printf("cleared: %d, e: %d\n",cleared[e],e);
				e++;
				y = n;
			}

			if(y == 0 && done !=n && resets !=2){
				y = n;
				resets ++;
				//printf("RESET RESET RESET RESET!!!!!!\n");
			}
		}

		for(k = 0; k < n; k++){
			if(finished[k] == 1){
				//printf("YYY: %d", y);
				deadlock_counter++;
				//cleared[g] = y;

				g++;
			}
		}
		//printf("DONE %d", done);
		if((deadlock_counter !=m && done != 1)||resets ==2) {
			deadlock_detected = 1;

		}

		if(done == n){
			deadlock_detected = 0;

		}
		y--;

	}


	//printf("Deadlocked: %d\n", deadlock_detected);
	//printf("--------------------------------------\n");
	//printf("\n");
	//printf("--------------------------------------\n");


	for(d = 0; d < n; d++){
		if(finished[d]==0){
			locked[c] =  d;
			printf("%d ", locked[d] + 1);
			c++;
		}
	}
	not_done = n - done;
	f = not_done-1;
	int a = 0, aa = 0, bb = 0, b = 0;
	int term_check = 0, terminated_true = 0, processed_true = 0;
	resets = 0;
	//printf("dafklms%d", f);
	while(not_done >= 0){

		while(f>=0){
			if(finished[f] == 0){
				for(term_check = 0; term_check < m; term_check++){
					if(request_array[f][term_check]<=T[term_check]){
						//printf("                R: %d T: %d, P: %d, ND: %d\n", request_array[f][term_check], T[term_check], f, not_done);
						t_counter++;

					}
				}
				//printf("COUNTER: %d\n", t_counter);
				if(t_counter == m){
					finished[f] = 1;
					processed[aa] = f;
					t_counter = 0;
					//printf("processed %d\n", f+1);
					aa++;
					resets = 0;
					for(a = 0; a < m; a++){
						//printf(" TT %d \n", T[p]);
						T[a] += allocation_array[f][a];
						//printf(" TT %d \n", T[p]);

					}
					processed_true = 1;
					f = n;
					terminated_true = 0;
					not_done--;
				}
				else if((t_counter!=m && terminated_true == 0 && processed_true == 0) ||(t_counter!=m && terminated_true == 1 && processed_true == 0 && resets != 0)){
					finished[f] = 1;
					terminated[b] = f+1;
					term_counter++;
					//printf("terminated: %d %d\n", f+1, b);
					b++;
					//end--;

					for(p = 0; p < m; p++){
						//printf(" TT %d \n", T[p]);
						T[p] += allocation_array[f][p];
						//printf(" TT %d \n", T[p]);

					}
					not_done--;

					terminated_true = 1;
					processed_true = 0;
					f = n;
					resets = 0;

				}
				//printf("F %d\n", f);
				//printf("processed true %d\n", processed_true);
				//printf("terminated true %d\n", terminated_true);
				t_counter = 0;
			}
			if((processed_true ==1 && f == 0)||((terminated_true == 1) && f == 0)){
					//printf("eresmia");
					resets++;
					f = n +1;
					terminated_true = 0;
					processed_true = 0;

				}
			f--;
//			if(f == 0 && terminated_true == 1 && processed_true == 0){
//				f = n;
//				terminated_true = 0;
//			}
			//printf("TERMINATED %d\n", terminated_true);
		}
		not_done--;
	}


	//printf("%d", not_done);
	//printf("\n");

	//printf("--------------------------------------\n");
	//printf("\n");
	//printf("--------------------------------------\n");

	if(deadlock_detected == 0){
		for(d = 0; d < n; d++){
			printf("%d ", cleared[d] + 1);

		}
	}else{
		printf("\n");
		for(d = 0; d < term_counter; d++){
			printf("%d ", terminated[d]);

		}
		printf("\n");
		for(d = 0; d < e; d++){
			printf("%d ", cleared[d] + 1);

		}
		for(bb = 0; bb < aa; bb++){
			printf("%d ", processed[bb] +1);
		}
	}
	//printf("%d ", cleared[1]);

}
