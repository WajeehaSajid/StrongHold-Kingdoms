#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

// ============================================================
//   CONSOLE COLOR SYSTEM
// ============================================================
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

enum Color {
    BLACK = 0, DARK_BLUE = 1, DARK_GREEN = 2, DARK_CYAN = 3,
    DARK_RED = 4, PURPLE = 5, DARK_YELLOW = 6, GRAY = 7,
    DARK_GRAY = 8, BLUE = 9, GREEN = 10, CYAN = 11,
    RED = 12, PINK = 13, YELLOW = 14, WHITE = 15
};

void setColor(Color text, Color bg = BLACK) {
    SetConsoleTextAttribute(hConsole, (bg << 4) | text);
}

void resetColor() { setColor(GRAY); }

void sleepSec(int s) { Sleep(s * 1000); }

int randomInRange(int low, int high) {
    return low + rand() % (high - low + 1);
}

// ============================================================
//   UI HELPER FUNCTIONS
// ============================================================

void printLine(char ch = '-', int len = 60, Color c = DARK_CYAN) {
    setColor(c);
    for (int i = 0; i < len; i++) cout << ch;
    cout << "\n";
    resetColor();
}

void printHeader(string title) {
    cout << "\n";
    printLine('=', 60, YELLOW);
    setColor(YELLOW);
    int pad = (60 - title.size()) / 2;
    for (int i = 0; i < pad; i++) cout << " ";
    cout << title << "\n";
    printLine('=', 60, YELLOW);
    resetColor();
}

void printSectionTitle(string title, Color c = CYAN) {
    cout << "\n";
    setColor(c);
    cout << "  >> " << title << "\n";
    setColor(DARK_CYAN);
    cout << "  ";
    for (int i = 0; i < 50; i++) cout << "-";
    cout << "\n";
    resetColor();
}

void printStat(string label, int value, Color labelColor = GRAY, Color valColor = WHITE) {
    setColor(labelColor);
    cout << "    " << label;
    // dot padding
    int dots = 28 - label.size();
    for (int i = 0; i < dots; i++) cout << ".";
    setColor(valColor);
    cout << " " << value << "\n";
    resetColor();
}

void printStatStr(string label, string value, Color labelColor = GRAY, Color valColor = GREEN) {
    setColor(labelColor);
    cout << "    " << label;
    int dots = 28 - label.size();
    for (int i = 0; i < dots; i++) cout << ".";
    setColor(valColor);
    cout << " " << value << "\n";
    resetColor();
}

void printEvent(string msg, Color c = YELLOW) {
    setColor(c);
    cout << "  [!] " << msg << "\n";
    resetColor();
}

void printSuccess(string msg) {
    setColor(GREEN);
    cout << "  [+] " << msg << "\n";
    resetColor();
}

void printDanger(string msg) {
    setColor(RED);
    cout << "  [-] " << msg << "\n";
    resetColor();
}

void printInfo(string msg) {
    setColor(CYAN);
    cout << "  [i] " << msg << "\n";
    resetColor();
}

void printDayBanner(int day) {
    cout << "\n\n";
    printLine('*', 60, PURPLE);
    setColor(PINK);
    string title = "  DAY " + to_string(day) + " OF 5  ";
    int pad = (60 - title.size()) / 2;
    for (int i = 0; i < pad; i++) cout << " ";
    cout << title << "\n";
    printLine('*', 60, PURPLE);
    resetColor();
}

void pressEnter() {
    setColor(DARK_GRAY);
    cout << "\n  Press ENTER to continue...";
    resetColor();
    cin.get();
}

// ============================================================
//   CLASSES
// ============================================================

class Society {
public:
    int peasants, merchants, nobles, military;

    Society() : peasants(500), merchants(100), nobles(50), military(150) {}

    void showStatus() {
        printSectionTitle("SOCIETY STATUS", CYAN);
        printStat("Peasants", peasants, GRAY, WHITE);
        printStat("Merchants", merchants, GRAY, YELLOW);
        printStat("Nobles", nobles, GRAY, PINK);
        printStat("Military", military, GRAY, GREEN);
    }

    void impactOfWar() {
        int loss = randomInRange(10, 50);
        peasants -= loss;
        military -= randomInRange(5, 20);
        printDanger("War impact: Lost " + to_string(loss) + " peasants & some troops.");
    }
};

class Army {
public:
    int soldiers, morale;
    string generalName;

    Army() : soldiers(150), morale(70), generalName("Unknown") {}

    void recruit(int num) {
        soldiers += num;
        morale += 5;
        printSuccess(to_string(num) + " soldiers recruited. Morale increased.");
    }

    void assignGeneral(string name) {
        generalName = name;
        morale += 10;
        printSuccess("General " + generalName + " assigned. Morale boosted.");
    }

    void battle() {
        printSectionTitle("BATTLE REPORT", RED);
        printEvent("Army is going to battle...", YELLOW);
        sleepSec(1);
        int loss = randomInRange(20, 70);
        soldiers -= loss;
        morale -= 15;
        printDanger("Battle ended. Lost " + to_string(loss) + " soldiers.");
        printStat("Remaining Soldiers", soldiers, GRAY, RED);
        printStat("Morale", morale, GRAY, YELLOW);
    }
};

class Politics {
public:
    string kingType;
    int politicalStability;

    Politics() : kingType("Elected"), politicalStability(70) {}

    void holdElection() {
        printSuccess("Election held. New king elected.");
        kingType = "Elected";
        politicalStability += 10;
    }

    void coupAttempt() {
        printSectionTitle("POLITICAL UPDATE", PURPLE);
        printEvent("Coup attempted!", PINK);
        int chance = randomInRange(1, 10);
        if (chance > 7) {
            kingType = "Military";
            politicalStability -= 20;
            printDanger("Coup SUCCESSFUL. Military king now in power!");
        }
        else {
            politicalStability -= 10;
            printSuccess("Coup FAILED. Kingdom holds.");
        }
    }

    void showPolitics() {
        printSectionTitle("POLITICAL STATUS", PURPLE);
        printStatStr("King Type", kingType, GRAY, PINK);
        printStat("Political Stability", politicalStability, GRAY,
            politicalStability > 50 ? GREEN : RED);
    }
};

class Economy {
public:
    int gold, taxRate, inflation;

    Economy() : gold(10000), taxRate(10), inflation(5) {}

    void collectTax(int population) {
        int collected = (population * taxRate) / 100;
        gold += collected;
        inflation += 1;
        printSuccess("Tax collected: " + to_string(collected) + " gold.");
    }

    void spendOnWelfare() {
        int amount = 500;
        if (gold >= amount) {
            gold -= amount;
            inflation -= 1;
            printSuccess("Spent " + to_string(amount) + " gold on public welfare.");
        }
        else {
            printDanger("Not enough gold for welfare!");
        }
    }

    void showEconomy() {
        printSectionTitle("ECONOMY STATUS", YELLOW);
        printStat("Treasury Gold", gold, GRAY, YELLOW);
        printStat("Tax Rate (%)", taxRate, GRAY, WHITE);
        printStat("Inflation (%)", inflation, GRAY, inflation > 10 ? RED : GREEN);
    }
};

class Bank {
public:
    int reserves;
    bool corruptionActive;

    Bank() : reserves(5000), corruptionActive(false) {}

    void loan(int amount) {
        if (reserves >= amount) {
            reserves -= amount;
            printSuccess("Loan granted: " + to_string(amount) + " gold.");
        }
        else {
            printDanger("Bank cannot grant this loan.");
        }
    }

    void detectFraud() {
        printSectionTitle("BANK AUDIT", DARK_YELLOW);
        int chance = randomInRange(1, 10);
        if (chance > 8) {
            corruptionActive = true;
            reserves -= 1000;
            printDanger("FRAUD DETECTED! Lost 1000 gold from reserves.");
        }
        else {
            printSuccess("No fraud found. Bank is clean.");
        }
    }

    void showBankStatus() {
        printSectionTitle("BANK STATUS", DARK_YELLOW);
        printStat("Bank Reserves", reserves, GRAY, reserves > 2000 ? GREEN : RED);
        printStatStr("Corruption", corruptionActive ? "YES" : "NO",
            GRAY, corruptionActive ? RED : GREEN);
    }
};

class Resource {
public:
    int food, wood, stone;

    Resource() : food(1000), wood(800), stone(600) {}

    void distribute(int people) {
        food -= people * 2;
        wood -= people;
        printInfo("Resources distributed to population.");
    }

    void showResources() {
        printSectionTitle("RESOURCES", GREEN);
        printStat("Food", food, GRAY, food > 300 ? GREEN : RED);
        printStat("Wood", wood, GRAY, wood > 300 ? GREEN : RED);
        printStat("Stone", stone, GRAY, stone > 200 ? GREEN : RED);
    }
};

class EconomyEvent {
public:
    void famine(Resource& r, Society& s) {
        printSectionTitle("RANDOM EVENT", RED);
        printEvent("FAMINE has struck the kingdom!", RED);
        r.food -= 500;
        s.peasants -= 100;
        printDanger("Lost 500 food and 100 peasants.");
    }

    void disaster(Resource& r) {
        printEvent("NATURAL DISASTER hit the kingdom!", RED);
        r.wood -= 200;
        r.stone -= 100;
        printDanger("Lost 200 wood and 100 stone.");
    }
};

class Market {
public:
    int goldRate;
    bool tradeBan;

    Market() : goldRate(100), tradeBan(false) {}

    void trade(string item) {
        printSectionTitle("MARKET TRADE", DARK_CYAN);
        if (tradeBan) {
            printDanger("Trade BANNED due to diplomatic issues.");
        }
        else {
            printSuccess("Traded: " + item + " at rate " + to_string(goldRate) + " gold.");
        }
    }

    void imposeBan() { tradeBan = true;  printDanger("Trade ban imposed."); }
    void liftBan() { tradeBan = false; printSuccess("Trade ban lifted."); }
};

// ============================================================
//   SPLASH SCREEN
// ============================================================
void showSplash() {
    system("cls");
    setColor(YELLOW);
    cout << R"(
  =====================================================================================
  |                                                                                   |
  |        SSSSS  TTTTT  RRRR   OOO   NN  N    GGGG      H  H   OOO  L     DD         |
  |        SS       T    R  R  O   O  NN  N   G          H  H  O   O L     D  D       |
  |         SSS     T    RRR   O   O  N N N  G   GG      HHHH  O   O L     D   D      |
  |           SS    T    R R   O   O  N  NN   G   G      H  H  O   O L     D  D       |
  |        SSSSS    T    R  R   OOO   N   N    GGGG      H  H   OOO  LLLLL DD         |   
  |                                                                                   |
  |                       K I N G D O M S   S I M U L A T O R                         |
  |                                                                                   |
  =====================================================================================
)";
    setColor(CYAN);
    cout << "\n        Build. Battle. Rule. Survive.\n";
    setColor(DARK_GRAY);
    cout << "\n        A 5-Day Kingdom Simulation in C++\n";
    resetColor();
    cout << "\n";
    printLine('=', 60, DARK_CYAN);
    pressEnter();
}

// ============================================================
//   MAIN GAME CONTROLLER
// ============================================================
class Stronghold {
public:
    Society society;
    Army army;
    Politics politics;
    Economy economy;
    Bank bank;
    Resource resource;
    Market market;
    EconomyEvent event;

    void runGame() {
        showSplash();

        for (int day = 1; day <= 5; day++) {
            system("cls");
            printDayBanner(day);

            society.showStatus();
            pressEnter();

            economy.collectTax(society.peasants + society.merchants);
            army.battle();
            pressEnter();

            politics.coupAttempt();
            bank.detectFraud();
            pressEnter();

            event.famine(resource, society);
            event.disaster(resource);
            pressEnter();

            market.trade("Silk");
            economy.spendOnWelfare();
            pressEnter();

            // --- End of Day Summary ---
            printHeader("END OF DAY " + to_string(day) + " SUMMARY");
            resource.showResources();
            economy.showEconomy();
            bank.showBankStatus();
            politics.showPolitics();

            if (day < 5) pressEnter();
        }

        // ---- GAME OVER SCREEN ----
        system("cls");
        printLine('=', 60, YELLOW);
        setColor(YELLOW);
        cout << "\n";
        cout << "         *** SIMULATION COMPLETE ***\n\n";
        resetColor();

        printSectionTitle("FINAL KINGDOM STATUS", CYAN);
        printStat("Peasants Left", society.peasants, GRAY, WHITE);
        printStat("Army Soldiers", army.soldiers, GRAY, GREEN);
        printStat("Treasury Gold", economy.gold, GRAY, YELLOW);
        printStat("Bank Reserves", bank.reserves, GRAY, CYAN);
        printStat("Political Stability", politics.politicalStability, GRAY,
            politics.politicalStability > 40 ? GREEN : RED);
        printStatStr("King Type", politics.kingType, GRAY, PINK);

        printLine('=', 60, YELLOW);
        setColor(CYAN);
        cout << "\n  Thank you for playing Stronghold Kingdoms!\n\n";
        resetColor();
    }
};

// ============================================================
//   MAIN
// ============================================================
int main() {
    srand(time(0));
    // Set console title
    SetConsoleTitleA("Stronghold Kingdoms Simulator");
    // Make console bigger
    system("mode con: cols=65 lines=45");

    Stronghold game;
    game.runGame();

    return 0;
}