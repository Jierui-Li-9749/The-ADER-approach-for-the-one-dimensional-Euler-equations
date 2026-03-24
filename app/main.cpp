#include "aderweno/test/task_3_1_weno5.hpp"
#include "aderweno/test/task_3_1_ader3.hpp"
#include "aderweno/test/task_3_1_ader4.hpp"
#include "aderweno/test/task_3_1_ader5.hpp"
#include "aderweno/test/task_3_2.hpp"
#include "aderweno/test/task_3_3.hpp"
#include "aderweno/test/task_3_4_convergence.hpp"
#include "aderweno/test/task_3_4_efficiency.hpp"

#include <iostream>
#include <string>

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cout << "Usage: ./aderweno1d <task>\n\n";
        std::cout << "Available tasks:\n";
        std::cout << "  3.1.weno5       convergence: WENO5 + SSP-RK3\n";
        std::cout << "  3.1.ader3       convergence: ADER3\n";
        std::cout << "  3.1.ader4       convergence: ADER4\n";
        std::cout << "  3.1.ader5       convergence: ADER5\n";
        std::cout << "  3.2             Sod and Lax shock tubes\n";
        std::cout << "  3.3             Titarev-Toro shock-turbulence\n";
        std::cout << "  3.4.convergence long-time convergence profile\n";
        std::cout << "  3.4.efficiency  CPU time vs L2 error\n";
        return 0;
    }

    const std::string task = argv[1];

    if      (task == "3.1.weno5")       aderweno::task_3_1_weno5();
    else if (task == "3.1.ader3")       aderweno::task_3_1_ader3();
    else if (task == "3.1.ader4")       aderweno::task_3_1_ader4();
    else if (task == "3.1.ader5")       aderweno::task_3_1_ader5();
    else if (task == "3.2")             task_3_2();
    else if (task == "3.3")             task_3_3();
    else if (task == "3.4.convergence") task_3_4_convergence();
    else if (task == "3.4.efficiency")  task_3_4_efficiency();
    else {
        std::cerr << "Unknown task: " << task << "\n";
        return 1;
    }

    return 0;
}