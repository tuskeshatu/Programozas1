void cube(double sidelen, double *area, double *volume)
{
    *area = 6 * sidelen * sidelen;
    *volume = sidelen * sidelen * sidelen;
}


int main()
{
    double sidelength = 3.5;

    // memoriafoglalas az eredmenynek
    double area;
    double volume;

    cube(sidelength, &area, &volume);

    return 0;
}