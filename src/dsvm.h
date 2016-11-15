void dsvm(int speed,
          int pwm_max,
          int torque_ref,
          int flux_ref,
          int torque,
          int flux,
          int * ru_out,
          int * rv_out,
          int * rw_out);

//Not type safe
#define setVec(x,y,z) do {  \
        ru = tmax*(vec[x][2] + vec[y][2] + vec[z][2])/3; \
        rv = tmax*(vec[x][1] + vec[y][1] + vec[z][1])/3; \
        rw = tmax*(vec[x][0] + vec[y][0] + vec[z][0])/3; \
        printf("Vec %i, %i, %i\n", x, y, z);          \
    } while (0)

#define vv_assign(x) do { \
        dir_vecs[x][0] = voltage_vecs[dir_vec[dv->v[x]]][0]; \
        dir_vecs[x][1] = voltage_vecs[dir_vec[dv->v[x]]][1]; \
        dir_vecs[x][2] = voltage_vecs[dir_vec[dv->v[x]]][2]; \
    } while (0)

#define threshold 1000000

//TODO: find real values for these, something like 1/6 and 1/2 of synchronous speed
#define high_th 1500
#define low_th 500

//Torque thresholds
//TODO: find good values for these
#define torque_high 20
#define torque_low 10

//TODO: maybe make this in to an enum?
#define low_speed 0
#define med_speed 1
#define high_speed 2

int clock6(int num1, int num2);

int torque_level(int torque_ref, int torque);

int sector_calc(int u_a, int u_b, int speed);

int speed_region(int speed);

struct dir_vector* low_speed_r(int sector, int tl, int fl);

struct dir_vector* med_speed_r(int sector, int dir, int tl, int fl);

struct dir_vector* high_speed_r(int sector, int dir, int tl, int fl);

struct dir_vector {
   int v[3];
};

static int voltage_vecs [8][3] =  
{
	{0,0,0},
	{0,0,1},
	{0,1,0},
	{0,1,1},
	{1,0,0},
	{1,0,1},
	{1,1,0},
	{1,1,1}
};

//These are a mechanism for translating between directional vectors and voltage vectors
// static int dir_vecs [8][3] =
// {
//   {0,0,0},
//   {0,0,1},
//   {0,1,1},
//   {0,1,0},
//   {1,1,0},
//   {1,0,0},
//   {1,0,1},
//   {1,1,1}
// }

static int dir_vec[8] =
{
  0, 1, 3, 2, 6, 4, 5, 7
};

//Offsets a bad name since 0->0 NOT zero offset!
static int low_speed_offsets [2][5][3] =
{
  {//-ve flux
    {-2,-2,-2}, //-2 torque
    {-2, 0, 0},
    { 0, 0, 0},
    { 2, 0, 0},
    { 2, 2, 2}  //+2 torque
  },
  {//+ve flux
    {-1,-1,-1}, //-2 torque
    {-1, 0, 0},
    { 0, 0, 0},
    { 1, 0, 0},
    { 1, 1, 1}  //+2 torque
  }
};

static int med_speed_offsets [2][2][5][3] = 
{
  {//-ve speed
    {//-ve flux
      {-2,-2,-2}, //-2 torque
      {-2,-2, 0},
      {-2, 0, 0},
      { 0, 0, 0},
      { 2, 2, 2}  //+2 torque
    },
    {//+ve flux
      {-1,-1,-1}, //-2 torque
      {-1,-1,-1},
      {-1,-1, 0},
      {-1, 0, 0},
      { 1, 1, 1}  //+2 torque
    }
  },
  {//+ve speed
    {//-ve flux
      {-2,-2,-2}, //-2 torque
      { 0, 0, 0},
      { 2, 0, 0},
      { 2, 2, 0},
      { 2, 2, 2}  //+2 torque
    },
    {//+ve flux
      {-1,-1,-1}, //-2 torque
      { 0, 0, 0},
      { 1, 0, 0},
      { 1, 1, 0},
      { 1, 1, 1}  //+2 torque
    }
  }
};

static int high_speed_offsets [2][2][2][5][3] = 
{
  {//-ve speed
    {//#- sector
      {//-ve flux
        {-2,-2,-2}, //-2 torque
        {-2,-2,-1},
        {-1,-2, 0},
        {-2, 0, 0},
        { 2, 2, 2}  //+2 torque
      },
      {//+ve flux
        {-1,-1,-1}, //-2 torque
        {-1,-1,-1},
        {-1,-1, 0},
        {-1, 0, 0},
        { 1, 1, 1}  //+2 torque
      }
    },
    {//#+ sector
      {//-ve flux
        {-2,-2,-2}, //-2 torque
        {-2,-2,-2},
        {-2,-2, 0},
        {-2, 0, 0},
        { 2, 2, 2}  //+2 torque
      },
      {//+ve flux
        {-1,-1,-1}, //-2 torque
        {-1,-1,-2},
        {-1,-2, 0},
        {-1, 0, 0},
        { 1, 1, 1}  //+2 torque
      }
    }
  },
  {//+ve speed
    {//#- sector
      {//-ve flux
        {-2,-2,-2}, //-2 torque
        { 2, 0, 0},
        { 1, 2, 0},
        { 2, 2, 1},
        { 2, 2, 2}  //+2 torque
      },
      {//+ve flux
        {-1,-1,-1}, //-2 torque
        { 1, 0, 0},
        { 1, 1, 0},
        { 1, 1, 1},
        { 1, 1, 1}  //+2 torque
      }
    },
    {//#+ sector
      {//-ve flux
        {-2,-2,-2}, //-2 torque
        { 2, 0, 0},
        { 2, 2, 0},
        { 2, 2, 2},
        { 2, 2, 2}  //+2 torque
      },
      {//+ve flux
        {-1,-1,-1}, //-2 torque
        { 1, 0, 0},
        { 1, 2, 0},
        { 1, 1, 2},
        { 1, 1, 1}  //+2 torque
      }
    }
  }
};