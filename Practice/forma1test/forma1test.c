typedef struct
{
    unsigned short int pole_position;
    double best_lap;
} qualifying_results;

typedef struct
{
    unsigned short racing_number;
    char name[3];
    qualifying_results qualifying_results[3];
} pilot;

pilot t[2] = {{1, "MSC", {{1, 67.423}, {3, 46.735}, {1, 70.264}}}, {2, "MAS", {{2, 67.433}, {5, 46.855}, {3, 70.317}}}};

/* int main(void)
{
    pilot t[2];

    t[0].racing_number = 1;
    strncpy(&t[0].name[0], "MSC", 3);
    t[0].qualifying_results[0].pole_position = 1;
    t[0].qualifying_results[1].pole_position = 3;
    t[0].qualifying_results[2].pole_position = 1;
    t[0].qualifying_results[0].best_lap = 67.423;
    t[0].qualifying_results[1].best_lap = 46.735;
    t[0].qualifying_results[2].best_lap = 70.264;

    t[1].racing_number = 2;
    strncpy(&t[1].name[0], "MAS", 3);
    t[1].qualifying_results[0].pole_position = 2;
    t[1].qualifying_results[1].pole_position = 5;
    t[1].qualifying_results[2].pole_position = 3;
    t[1].qualifying_results[0].best_lap = 67.433;
    t[1].qualifying_results[1].best_lap = 46.855;
    t[1].qualifying_results[2].best_lap = 70.317;

    return 0;
}*/