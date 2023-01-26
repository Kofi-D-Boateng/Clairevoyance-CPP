#include <iostream>
#include <vector>
using namespace std;
int main(int argc, char const *argv[])
{
    double data_points[10] = {20.15, 21.43, 23.01, 32.19, 30.09, 28.13, 29.10, 31.00, 33.47, 32.86};
    vector<double> weighted_dps;
    int start{0}, end{1}, eoc{9};
    double window{2.0}, totalWeights{0.0};
    while (end != eoc)
    {
        int counter{0};
        double ema = data_points[start];
        double alpha = 2.0 / (window + 1);
        double currWeight = 0;
        std::cout << "--------------- Starting accumulation -------------------" << endl;
        while (counter++ != window)
        {
            currWeight += alpha;
            std::cout << "\nCurrent Window Count: " << counter << endl;
            std::cout << "Current data point: " << data_points[end] << endl;
            // std::cout << "Current Weight: " << currWeight << endl;
            std::cout << "Previous ema: " << ema << endl;
            double part1{(data_points[end++] * alpha)}, part2{(ema * (1 - alpha))};
            std::cout << "Part one= " << part1 << endl;
            std::cout << "Part two= " << part2 << endl;
            double curr_ema = part1 + part2;
            std::cout << "New ema: " << curr_ema << endl;
            ema = curr_ema;
        }
        weighted_dps.push_back(ema);
        start++;
        end = start + 1;
        counter = 0;
    }

    std::cout << "-------------------- Data Points ----------------------" << endl;
    for (auto &dp : data_points)
    {
        std::cout << dp << endl;
    }
    std::cout << "-------------------- Weighted Data Points ----------------------" << endl;
    for (auto &wd : weighted_dps)
    {
        std::cout << wd << endl;
    }
    /* code */
    return 0;
}