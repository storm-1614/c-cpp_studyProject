struct rec
{
    int i;
    int j;
    int a[2];
    int *p;
};

int main(int argc, char *argv[])
{
    struct rec *r;
    r->p = &r->a[r->i + r->j];
    return 0;
}
