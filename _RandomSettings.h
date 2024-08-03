#ifndef RANDOMSETTINGS_H
#define RANDOMSETTINGS_H

class RandomSettings {

private:

    int number;

public:

    RandomSettings() {
        unsigned seed = time(0);
        srand(seed);
        number = 0;
    }

    // losowa liczba z przedzia³u
    int getRandomInt(int min, int max) {

        number = (rand() % (max - min + 1)) + min;
        return number;
    }

    // losowe dru¿yny 
    int* createRandomOrderIndexes(int size) {
        int* ptr = new int[size];
        vector<int>indexes;

        for (int i = 0; i < size; i++)
        {
            indexes.push_back(i+1);
        }

        for (int i = 0; i < size; i++)
        {
            int rnd = getRandomInt(1, size);

            ptr[i] = indexes[rnd];

            swap(indexes[rnd], indexes[size - 1]);

            indexes.pop_back();
        }

        return ptr;
    }

    void swap(int& x, int& y) {

        int temp;
        temp = y;
        y = x;
        x = temp;
    }

};


#endif // !RANDOMSETTINGS_H
