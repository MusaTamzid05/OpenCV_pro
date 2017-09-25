
#include "categorize.h"
int main(int argc, char *argv[])
{
    int cluster = 1000;   
    Categorize categorize(cluster);
    categorize.build_vocab();

    categorize.train_classifier();
    categorize.categorize();
    return 0;
}
