
void modsvm_2(int u_a,
              int u_b,
              int pwm_max,
              int torque_ref,
              int flux_ref,
              int torque,
              int flux,
              int * ru_out,
              int * rv_out,
              int * rw_out);


int pickVec(int torque_ref, int flux_ref, int torque, int flux);

int sector_calc(int u_a, int u_b);
    
//Old vector table for simple modsvm
//Issue: selects vector which will increase torque/flux each time, doesn't just sector switching table
static int vec [8][3] =  
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

//Group of vector tables for flux/torque modsvm
static int sector_1 [4][3] =  
{
        {0,1,1}, //V3
        {1,0,1}, //V5
        {0,1,0}, //V2
        {1,0,0}, //V4
};

static int sector_2 [4][3] =  
{
        {0,1,0}, //V2
        {0,0,1}, //V1
        {1,1,0}, //V6
        {1,0,1}, //V5
};

static int sector_3 [4][3] =  
{
        {1,1,0}, //V6
        {0,1,1}, //V3
        {1,0,0}, //V4
        {0,0,1}, //V1
};

static int sector_4 [4][3] =  
{
        {1,0,0}, //V4
        {0,1,0}, //V2
        {1,0,1}, //V5
        {0,1,1}, //V3
};

static int sector_5 [4][3] =  
{
        {1,0,1}, //V5
        {1,1,0}, //V6
        {0,0,1}, //V1
        {0,1,0}, //V2
};

static int sector_6 [4][3] =  
{
        {0,0,1}, //V1
        {1,0,0}, //V4
        {0,1,1}, //V3
        {1,1,0}, //V6
};

//This is just the above tables coalesced together for easier access.
static int sectors [6][4][3] =
{
    {//Sector 1
        {0,1,1}, //V3
        {1,0,1}, //V5
        {0,1,0}, //V2
        {1,0,0}, //V4
    },
    {//Sector 2
        {0,1,0}, //V2
        {0,0,1}, //V1
        {1,1,0}, //V6
        {1,0,1}, //V5
    },
    {//Sector 3
        {1,1,0}, //V6
        {0,1,1}, //V3
        {1,0,0}, //V4
        {0,0,1}, //V1
    },
    {//Sector 4
        {1,0,0}, //V4
        {0,1,0}, //V2
        {1,0,1}, //V5
        {0,1,1}, //V3
    },
    {//Sector 5
        {1,0,1}, //V5
        {1,1,0}, //V6
        {0,0,1}, //V1
        {0,1,0}, //V2
    },
    {//Sector 6
        {0,0,1}, //V1
        {1,0,0}, //V4
        {0,1,1}, //V3
        {1,1,0}, //V6
    }
};

