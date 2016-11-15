#include "modsvm_2.h"
#include <stdlib.h>
#include <stdio.h> 
// #include <simstruc.h>

//Not type safe
#define setVec(s, x) do {  \
		ru = sectors[s][x][2] == 0 ? 0 : tmax; \
		rv = sectors[s][x][1] == 0 ? 0 : tmax; \
		rw = sectors[s][x][0] == 0 ? 0 : tmax; \
		curVec = x;                     \
		printf("Vec %i\n", x);          \
	} while (0)


int pickVec(torque_ref, flux_ref, torque, flux) 
{
    int torque_diff = torque_ref - torque;
    int flux_diff   = flux_ref - flux;

    if (flux_diff > 0 && torque_diff > 0) return 0;
    if (flux_diff > 0 && torque_diff < 0) return 1;
    if (flux_diff < 0 && torque_diff > 0) return 2;
    if (flux_diff < 0 && torque_diff < 0) return 3;

    //if equal
    return 0;
}


#define threshold 1000000

int sector_calc(int u_a, int u_b) 
{
    //Scale u_b to make if statements easier
    u_b = (u_b * 56756) >> 15; 

    printf("u_b scaled:%i\n", u_b);

    if (u_a > 0) {
        //either 1,2,6
        if (u_b > u_a) {
            //Zone 2
            printf("Zone 2\n");
 
            return 2;
        } else if (-u_b > u_a) {
            //Zone 6
            printf("Zone 6\n");

            return 6;
        } else {
            //Zone 1
            printf("Zone 1\n");
            return 1;
        }
    } else {
        //either 3,4,5
        if (u_b > -u_a) {
            //Zone 3
            printf("Zone 3\n");

            return 3;
        } else if (-u_b > -u_a) {
            //Zone 5
            printf("Zone 5\n");
            return 5;
        } else {
            //Zone 4
            printf("Zone 4\n");
            return 4;
        }
    }
    return -1;
}

void modsvm_2(int u_a,
              int u_b,
              int pwm_max,
              int torque_ref,
              int flux_ref,
              int torque,
              int flux,
              int * ru_out,
              int * rv_out,
              int * rw_out)
{
    int curVec = -1;
    int ru, rv, rw;
    int tmax = pwm_max; //TODO: this is redundant?
    int selector = pickVec(torque_ref, flux_ref, torque, flux);
    int sector = sector_calc(u_a, u_b); // this will be replaced once we figure out how to calculate the angle without u_a and u_b

    printf("curVec: %i", curVec);
    // Select between zero vector and selected vector
    if(1 > threshold) {

    	//TODO: use historic info to select best between v0 and v7
    	printf("Vec Zero\n");


        //TODO: zero vector stuff here
    	//setVec(0);

    } else {
        setVec(sector-1, selector);
    }

    //Ensure 0 <= ru, rv, rw <= tmax
    *ru_out = (ru < 0 ? 0 : (ru > tmax ? tmax : ru));
    *rv_out = (rv < 0 ? 0 : (rv > tmax ? tmax : rv));
    *rw_out = (rw < 0 ? 0 : (rw > tmax ? tmax : rw));

}