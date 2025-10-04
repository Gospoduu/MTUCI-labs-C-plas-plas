#include <iostream>

using namespace std;

// format output
string delete_zeros(string s) {
    int last_not_zero = s.length() - 1;
    for (int i = last_not_zero; i >= 0; i--) {
        if (s[i] != '0') {
            break;
        }
        last_not_zero -=1;
    }
    string new_s = s.substr(0, last_not_zero + 1);
    return new_s;
}

int main()
{
    //splits
    int N = 500;
    double a = 10, b = 50;
    int splits_cnt = 4;
    int dot_splits_cnt = splits_cnt + 1;
    double ranges[dot_splits_cnt];
    double step = (b - a)/splits_cnt;
    ranges[0] = a;
    for (int i = 1; i < dot_splits_cnt; i++)
    {
        ranges[i] = ranges[i - 1] + step;
        // cout << ranges[i] << endl;
    }
    // random array
    double nums[N];
    srand(time(0));
    for (int i = 0 ; i < N ; i ++) {
        double rand_d = rand();
        nums[i] = rand_d/RAND_MAX * (b - a) + a;
        // cout << nums[i] << endl;
    }
    // sort random array
    for (int i = 0 ; i < N - 1; i ++) {
        for (int j = i + 1 ; j < N ; j ++) {
            if (nums[i] > nums[j]) {
                nums[j] = nums[i] + nums[j];
                nums[i] = nums[j] - nums[i];
                nums[j] = nums[j] - nums[i];
            }
        }
    }
    // get element on splits
    int last_split = 1;
    string splits_counter[splits_cnt];
    int last_idx = 0;
    for (int i = 1; i < dot_splits_cnt; i++) {
        double l_border = ranges[i - 1];
        double r_border = ranges[i];
        splits_counter[i - 1] = delete_zeros(to_string(l_border)) + " <= n < " + delete_zeros(to_string(r_border)) + " ";
        for (int j = last_idx; j < N; j++) {
            if (r_border == b) {
                if (nums[j] > r_border) {
                    last_idx = j;
                    break;
                }
            }
            else if (nums[j] >= r_border) {
                last_idx = j;
                break;
            }
            splits_counter[i - 1] += "*";
        }
    }
    for (int i = 0; i < splits_cnt; i++) {
        cout << splits_counter[i] << endl;
    }
}
