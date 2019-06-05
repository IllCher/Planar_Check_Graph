#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;
typedef struct ans ans;
struct ans{
    bool check;
    int a[6];
};
bool check_link(int** a, int ind1, int ind2) {
    return a[ind1][ind2] > 0;
}
bool check_k5_comb(int** a, int* v) {
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (!check_link(a,v[i],v[j])) {
                return false;
            }

        }
    }
    return true;
}

bool check_k33_comb(int** a, int* v) {
    for (int i = 0; i < 3; i++) {
        for (int j = 3; j < 6; j++) {
            if (!check_link(a,v[i],v[j])) {
                return false;
            }

        }
    }
    return true;
}


ans check_5_subgraph(int** a, int size) {
    ans answ;
    int usable[5] = {0,1,2,3,4};
    for (int a1 = 0; a1 < size; a1++) {
        for(int a2 = 0; a2 < size; a2++) {
                if (a1 == a2) continue;
            for (int a3 = 0; a3 < size; a3++) {
                if (a3 == a2 ||a3 == a1) continue;
                for(int a4 = 0; a4 < size; a4++) {
                    if (a4 == a1 ||a4 == a2||a4 == a3) continue;
                    for(int a5 = 0; a5 < size; a5++) {
                        if (a5 == a1 ||a5 == a2||a5 == a3||a5 == a4) continue;
                        usable[0] = a1;
                        usable[1] = a2;
                        usable[2] = a3;
                        usable[3] = a4;
                        usable[4] = a5;
                        if (check_k5_comb(a,usable)) {
                            answ.check = true;
                            for (int i = 0; i < 5; i++) {
                                answ.a[i] = usable[i];
                            }
                            return answ;
                        }
                    }
                }
            }
        }
    }
    answ.check = false;
    return answ;
}

ans check_33_subgraph(int** a, int size) {
    ans answ;
    int usable[6] = {0,1,2,3,4,5};
    if (size < 6) {
        answ.check = false;
        return answ;
    }
    for (int a1 = 0; a1 < size; a1++) {
        for(int a2 = 0; a2 < size; a2++) {
                if (a1 == a2) continue;
            for (int a3 = 0; a3 < size; a3++) {
                if (a3 == a2 ||a3 == a1) continue;
                for(int a4 = 0; a4 < size; a4++) {
                    if (a4 == a1 ||a4 == a2||a4 == a3) continue;
                    for(int a5 = 0; a5 < size; a5++) {
                        if (a5 == a1 ||a5 == a2||a5 == a3||a5 == a4) continue;
                        for(int a6 = 0; a6 < size; a6++) {
                            if (a6 == a1 ||a6 == a2||a6 == a3||a6 == a4 || a6 == a5) continue;
                            usable[0] = a1;
                            usable[1] = a2;
                            usable[2] = a3;
                            usable[3] = a4;
                            usable[4] = a5;
                            usable[5] = a6;
                            if (check_k33_comb(a,usable)) {
                                 answ.check = true;
                                 for (int i = 0; i < 6; i++) {
                                    answ.a[i] = usable[i];
                                 }
                                 return answ;
                            }
                        }
                    }
                }
            }
        }
    }
    answ.check = false;
    return answ;
}
int main(int argc, char *argv[]) {
    //Loading matrix
    ifstream in(argv[1]);
    int size = 0, i, j;
    in >> size;
    int** matrix;
    matrix = new int*[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
    }
    for(i = 0; i < size; i++) {
        for(j = 0;j < size; j++) {
            in >> matrix[i][j];
        }
    }
    in.close();
    //////// Algorithm Difficulty: O(n^6)
    if (size < 5) {
        cout << "graph is planar" << endl;
    } else {
        ans answ5 = check_5_subgraph(matrix,size);
        ans answ6 = check_33_subgraph(matrix,size);
        fstream out;
        out.open(argv[1]);
        out.clear();
        if (answ5.check) {
            out << size << endl;
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    out << matrix[i][j] << " ";
                }
                out<<endl;
            }
            out << "Colors_Nodes:" << endl;
            for (int i = 0; i < size; i++) {
                bool k = false;
                for (int j = 0; j < 5; j++) {
                    if (answ5.a[j] == i) {
                        out << answ5.a[i] << " " << "Red" << endl;
                        k = true;
                        break;
                    }
                }
                if (!k) {
                    out << i << " " << "Green" << endl;
                }
            }
            out << "Colors_Edges:" << endl;
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    if (i != j) {
                        out << answ5.a[i] << " " << answ5.a[j] << " " << "Red" << endl;
                    }
                }

            }
        } else if (answ6.check) {
            out << size << endl;
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    out << matrix[i][j] << " ";
                }
                out<<endl;
            }
            out << "Colors_Nodes:" << endl;
            for (int i = 0; i < size; i++) {
                bool k = false;
                for (int j = 0; j < 6; j++) {
                    if (answ6.a[j] == i) {
                        out << answ6.a[i] << " " << "Red" << endl;
                        k = true;
                        break;
                    }
                }
                if (!k) {
                    out << i << " " << "Green" << endl;
                }
            }
            out << "Colors_Edges:" << endl;
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 6; j++) {
                    if (check_link(matrix,answ6.a[i],j)) {
                        out << answ6.a[i] << " " << j << " " << "Red" << endl;
                    }
                }
            }
        } else {
            cout << "graph is planar" << endl;
        }
        out.close();
    }
    return 0;
}
