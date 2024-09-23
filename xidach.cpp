#include <iostream>
#include <vector> // thay vì dùng mảng thì dùng vector
#include <cstdlib>
#include <ctime>

using namespace std;

// Ham phat sinh mot la bai ngau nhien tu 1 den 11
int drawCard() {
    int card = rand() % 13 + 1;
    if (card > 10) {  // J, Q, K deu co gia tri la 10
        card = 10;
    }
    return card;
}

// Ham tinh tong diem cua bo bai
int calculateTotal(const vector<int> &hand) {
    int total = 0;
    int aceCount = 0;

    for (int card : hand) {
        total += card;
        if (card == 1) {  // Xu ly quan At
            aceCount++;
        }
    }

    // Neu tong diem qua lon va co quan At thi giam gia tri At tu 11 thanh 1
    while (total <= 11 && aceCount > 0) {
        total += 10;  // At co gia tri 11
        aceCount--;
    }

    return total;
}

// Ham in ra cac la bai trong tay
void printHand(const vector<int> &hand) {
    for (int card : hand) {
        if (card == 1) {
            cout << "A ";
        } else if (card == 11) {
            cout << "J ";
        } else if (card == 12) {
            cout << "Q ";
        } else if (card == 13) {
            cout << "K ";
        } else {
            cout << card << " ";
        }
    }
    cout << endl;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    // Phat bai cho nguoi choi va nha cai
    vector<int> playerHand;
    vector<int> dealerHand;

    // Nguoi choi duoc phat 2 la bai
    playerHand.push_back(drawCard());
    playerHand.push_back(drawCard());

    // Nha cai duoc phat 2 la bai
    dealerHand.push_back(drawCard());
    dealerHand.push_back(drawCard());

    // In ra bai cua nguoi choi
    cout << "Bai cua ban Mai Xuan: ";
    printHand(playerHand);
    cout << "Tong diem: " << calculateTotal(playerHand) << endl;

    // Vong lap cho phep nguoi choi chon rut bai hoac dung
    int choice;
    bool playerBust = false;

    while (true) {
        cout << "Nhan 1 de rut bai, nhan 0 de dung: ";
        cin >> choice;

        if (choice == 1) {
            playerHand.push_back(drawCard());
            cout << "Bai cua ban Mai Xuan: ";
            printHand(playerHand);
            int playerTotal = calculateTotal(playerHand);
            cout << "Tong diem: " << playerTotal << endl;

            if (playerTotal > 21) {
                cout << "Ban bi quac, leu leu choi ngu !" << endl;
                playerBust = true;
                break;
            }
        } else if (choice == 0) {
            break;
        } else {
            cout << "Lua chon khong hop le, noi dung hon la lua chon ngu!" << endl;
        }
    }

    // Xu ly luot cua nha cai neu nguoi choi khong bi quac
    if (!playerBust) {
        cout << "Bai cua nha cai: ";
        printHand(dealerHand);
        int dealerTotal = calculateTotal(dealerHand);
        cout << "Tong diem cua nha cai: " << dealerTotal << endl;

        while (dealerTotal < 16) {
            cout << "Nha cai rut them bai..." << endl;
            dealerHand.push_back(drawCard());
            printHand(dealerHand);
            dealerTotal = calculateTotal(dealerHand);
            cout << "Tong diem cua nha cai: " << dealerTotal << endl;
        }

        if (dealerTotal > 21) {
            cout << "Nha cai bi quac, Mai Xuan thang!" << endl;
        } else {
            // So sanh diem cua nguoi choi va nha cai
            int playerTotal = calculateTotal(playerHand);
            cout << "Tong diem cua Mai Xuan: " << playerTotal << endl;
            cout << "Tong diem cua nha cai: " << dealerTotal << endl;

            if (playerTotal > dealerTotal) {
                cout << "Mai Xuan thang!" << endl;
            } else if (playerTotal < dealerTotal) {
                cout << "Nha cai thang!" << endl;
            } else {
                cout << "Hoa!" << endl;
            }
        }
    }

    return 0;
}
