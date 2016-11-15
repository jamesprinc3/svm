/*
    Please see DSVM.pdf for some context to this code.
*/

#include "dsvm.h"
#include <stdlib.h>
#include <stdio.h>
//#include <simstruc.h>

//Not type safe
// #define setVec(x) do {  \
//         ru = vec[x][2] == 0 ? 0 : tmax; \
//         rv = vec[x][1] == 0 ? 0 : tmax; \
//         rw = vec[x][0] == 0 ? 0 : tmax; \
//         curVec = x;                     \
//         printf("Vec %i\n", x);          \
//     } while (0)


int clock6(int num1, int num2) 
{
    int result = num1 + num2;
    if (result < 1) return result + 6;
    if (result > 6) return result - 6;

    return 0;
}

//TODO: maybe turn this in to a macro?
int torque_level(int torque_ref, int torque)
{
    int torque_abs_diff = abs(torque_ref - torque);

    if (torque < torque_ref && torque_abs_diff > torque_high) return  2;
    if (torque < torque_ref && torque_abs_diff > torque_low)  return  1;
    if (torque > torque_ref && torque_abs_diff > torque_high) return -2;
    if (torque > torque_ref && torque_abs_diff > torque_low)  return -1;  

    return 0;
}

//input: speed: 0->low, 1->med, 2->high
//output: 1-6 -> 1-6 for low/med, 1- - 6- for high
//        7-12 ->  1+-6+ for high, N/A for low/med
int sector_calc(int u_a, int u_b, int speed)
{
    int u_b_60 = (u_b * 18918) >> 15; //Scale by 1/sqrt(3) in order to split sectors into +/-
    u_b = (u_b * 56756) >> 15;  //Note: scale by sqrt(3) for *u_b* only
    //int u_b_60 = (u_b * trans_60) >> 15;  //Note: scale by sqrt(3) for *u_b* only

    if (speed == high_speed) {
        if (u_a > 0) {
            //either 1,2,6
            if (u_b > u_a) {
                //Zone 2
                printf("Zone 2\n");
                return (u_b_60 < u_a ? 2 : 8);
            } else if (-u_b > u_a) {
                //Zone 6
                printf("Zone 6\n");
                return (-u_b_60 > u_a ? 6 : 12); 
            } else {
                //Zone 1
                printf("Zone 1\n");
                return (u_b < 0 ? 1 : 7);
            }
        } else {
            //either 3,4,5
            if (u_b > -u_a) {
                //Zone 3
                printf("Zone 3\n");
                return (u_b_60 > -u_a ? 3 : 9);
            } else if (-u_b > -u_a) {
                //Zone 5
                printf("Zone 5\n");
                return (-u_b_60 < -u_a ? 5 : 11);
            } else {
                //Zone 4
                printf("Zone 4\n");
                return (u_b > 0 ? 4 : 10);
            }
        }
    } 
    if (speed == low_speed || speed == med_speed) 
    {
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
    }
    return 0;
}

int speed_region(int speed)
{
    int s = abs(speed);

    if (s > high_th) return high_speed;
    if (s < low_th)  return low_speed;
    return med_speed; 
}

void dsvm(int speed,
          int pwm_max,
          int torque_ref,
          int flux_ref,
          int torque,
          int flux,
          int * ru_out,
          int * rv_out,
          int * rw_out)
{
    //UNUSED: Can be used to pick between v0 and v7
    // static int curVec = -1;

    int tmax = pwm_max;
    int ru,rv,rw;

    int speed_r = speed_region(speed);
    int sector = sector_calc(torque, flux, speed_r);

    // Select zone
    //TODO: find threshold!
    if(1 > threshold) {

        //TODO: use historic info to select best between v0 and v7
        printf("Vec Zero\n");

        // setVec(0);
        
    } else {
        int tl = 2 + torque_level(torque_ref, torque);
        int fl = flux_ref > flux ? 0 : 1;
        int dir = speed < 0 ? 0 : 1;

        struct dir_vector *dv;

        if (speed_r == low_speed)  dv = low_speed_r (sector, tl, fl);
        if (speed_r == med_speed)  dv = med_speed_r (sector, dir, tl, fl);
        if (speed_r == high_speed) dv = high_speed_r(sector, dir, tl, fl);

        int dir_vecs [3][3];
        //Maybe coalecse these 3 macro calls in to 1?
        vv_assign(0);
        vv_assign(1);
        vv_assign(2);

        //possible issue in evaluation ordering
        //slightly ugly, move to macro?
        ru = (dir_vecs[0][0]+dir_vecs[0][1]+dir_vecs[0][2])*(tmax/3);
        rv = (dir_vecs[1][0]+dir_vecs[1][1]+dir_vecs[1][2])*(tmax/3);
        rw = (dir_vecs[2][0]+dir_vecs[2][1]+dir_vecs[2][2])*(tmax/3);
    }

    //Ensure 0 <= ru, rv, rw <= tmax
    *ru_out = (ru < 0 ? 0 : (ru > tmax ? tmax : ru));
    *rv_out = (rv < 0 ? 0 : (rv > tmax ? tmax : rv));
    *rw_out = (rw < 0 ? 0 : (rw > tmax ? tmax : rw));

}

struct dir_vector* low_speed_r(int sector, int tl, int fl)
{
    struct dir_vector *dv = (struct dir_vector *)malloc(sizeof(struct dir_vector));

    dv->v[0] = low_speed_offsets[tl][fl][0] == 0 ? 0 : sector + low_speed_offsets[tl][fl][0];
    dv->v[1] = low_speed_offsets[tl][fl][1] == 0 ? 0 : sector + low_speed_offsets[tl][fl][1];
    dv->v[2] = low_speed_offsets[tl][fl][2] == 0 ? 0 : sector + low_speed_offsets[tl][fl][2];

    return dv;
}

struct dir_vector* med_speed_r(int sector, int dir, int tl, int fl)
{
    struct dir_vector *dv = (struct dir_vector *)malloc(sizeof(struct dir_vector));

    dv->v[0] = med_speed_offsets[dir][tl][fl][0] == 0 ? 0 : sector + med_speed_offsets[dir][tl][fl][0];
    dv->v[1] = med_speed_offsets[dir][tl][fl][1] == 0 ? 0 : sector + med_speed_offsets[dir][tl][fl][1];
    dv->v[2] = med_speed_offsets[dir][tl][fl][2] == 0 ? 0 : sector + med_speed_offsets[dir][tl][fl][2];

    return dv;
}

struct dir_vector* high_speed_r(int sector, int dir, int tl, int fl)
{
    struct dir_vector *dv = (struct dir_vector *)malloc(sizeof(struct dir_vector));

    int sec = sector - 1 / 6;

    dv->v[0] = high_speed_offsets[sec][dir][tl][fl][0] == 0 ? 0 : sector + high_speed_offsets[sec][dir][tl][fl][0];
    dv->v[1] = high_speed_offsets[sec][dir][tl][fl][1] == 0 ? 0 : sector + high_speed_offsets[sec][dir][tl][fl][1];
    dv->v[2] = high_speed_offsets[sec][dir][tl][fl][2] == 0 ? 0 : sector + high_speed_offsets[sec][dir][tl][fl][2];

    return dv;
}

