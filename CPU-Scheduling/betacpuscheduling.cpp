#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Job {
    string name;
    int r;
    int p;
    int d;
    int remaining;
    int completion = -1;
};

int main() {
    vector<Job> jobs = {
        {"j1", 0, 10, 12},
        {"j2", 3, 15, 20},
        {"j3", 5, 3, 10},
        {"j4", 1, 7, 10},
        {"j5", 6, 9, 10},
        {"j6", 2, 2, 5},
        {"j7", 1, 5, 7},
        {"j8", 6, 8, 16},
        {"j9", 8, 11, 20},
        {"j10", 0, 1, 20}
    };

    for (auto& j : jobs) j.remaining = j.p;

    const int CPU_COUNT = 3;

    vector<vector<string>> gantt(CPU_COUNT);
    int t = 0;

    int unfinished = jobs.size();
    int MAX_T = 200;

    while (unfinished > 0 && t < MAX_T) {
        vector<int> ready;

        for (int i = 0; i < jobs.size(); i++)
            if (jobs[i].r <= t && jobs[i].remaining > 0)
                ready.push_back(i);

        sort(ready.begin(), ready.end(), [&](int a, int b) {
            return jobs[a].d < jobs[b].d;
            });

        vector<int> chosen;

        for (int i = 0; i < CPU_COUNT; i++) {
            if (i < ready.size())
                chosen.push_back(ready[i]);
            else
                chosen.push_back(-1);
        }

        for (int cpu = 0; cpu < CPU_COUNT; cpu++) {
            if (chosen[cpu] == -1) {
                gantt[cpu].push_back(" - ");
                continue;
            }


            
            int j = chosen[cpu];
            jobs[j].remaining--;

            gantt[cpu].push_back(jobs[j].name);

            if (jobs[j].remaining == 0) {
                jobs[j].completion = t + 1;
                unfinished--;
            }
        }



        t++;
    }

    cout << "\n===== GANTT CHART (EDF, 3 CPUs) =====\n\n";

    for (int cpu = 0; cpu < CPU_COUNT; cpu++) {
        cout << "CPU" << cpu + 1 << ": ";
        for (auto& slot : gantt[cpu]) cout << slot << " ";
        cout << "\n";
    }

    cout << "\n===== JOB COMPLETION TIMES =====\n\n";

    for (auto& j : jobs) {
        cout << j.name
            << "  r=" << j.r
            << "  p=" << j.p
            << "  d=" << j.d
            << "  -> completion: " << j.completion;



        if (j.completion <= j.d)
            cout << "   meets deadline\n";
        else
            cout << "   misses deadline\n";
    }




    return 0;
}
