#include <iostream>
#include <chrono>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <cstring>
#include <string>
#include <algorithm>
#include <array>
#include <vector>
#include <deque>
#include <set>
#include <bitset>
#include <unordered_set>
#include <map>
#include <queue>
#include <stack>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
#define AboTaha_on_da_code ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define X first
#define Y second

const int dx[8]={0, 0, 1, -1, 1, -1, -1, 1}, dy[8]={1, -1, 0, 0, 1, -1, 1, -1}, M = 1e9+7, M2 = 998244353;

enum Type {
    LE, GE, EQ
};

enum Result {
    OK, UNBOUND, UNFEASIBLE
};
enum OFType {
    MAX, MIN
}; //objective funtion type (maximize or minimize)
#define INF 1e30
#define EPS 1e-9
#define LD long double //Percision does matter in this algorithm
struct SimplexModel {
/*****Data Structures*****/
//Constraints
    vector<vector<LD> > lhs; //matrix of constraints coefficients
            vector<LD> rhs; //right hand side of constraints
    vector<Type> constraintTypes; //type of constraint (greater than or equal, equal ... etc)
//Objective Function
    vector<LD> of; //coefficients of variables in objective function
            OFType oftype;
//Variables
    vector<bool> unRestricted; //unRestricted[i] is true iff variable[i] can be -ve
//Values of variable in the solution (output only, don't fill)
    vector<LD> solution;
//Internal use data structures (don't fill from outside)
    int nVar, nCon; //number of variables/constraints
    vector<int> negativePart; //index of negative part of unrestricted variables
    vector<int> positivePart; //index of positive part of unrestricted variables
    vector<bool> isNegativePart; //isNegativePart[i] = true iff variable i is x2 in (x=x1-x2)
    vector<int> basic; //indicies of variables in the current solution (initially slacks and artificials)
    vector<bool> isArtificial; //isArtificial[i] = true iff variable[i] is artificial
/*****Data Structures*****/
/******Methods******/
//Add new variable to the model (used to add slacks, artificials, negative parts and surpluses) and return its index
    int addVariable() {
//Add variable to LHS
        for (int i = 0; i < lhs.size(); i++)
            lhs[i].push_back(0);
//Add varaible to Objective funtion
        of.push_back(0);
        isArtificial.push_back(false); //default value, might be modified later
        isNegativePart.push_back(false); //default value, might be modified later
        positivePart.push_back(0);
//Return variable index
        return nVar++;
    }
//Standardize model
    void standardize() {
//Initialize internal data structures
        nVar = unRestricted.size();
        nCon = lhs.size();
        negativePart.resize(nVar);
        positivePart.resize(nVar);
        isNegativePart.clear();
        isNegativePart.resize(nVar, false);
        basic.clear();
        solution.clear();
        solution.resize(nVar, 0);
        isArtificial.clear();
        isArtificial.resize(nVar, false);
        int i, j, varIdx;
//Objective function should be max
        if (oftype == MIN) {
            for (i = 0; i < nVar; i++)
                of[i] *= -1;
            oftype = MAX;
        }
//Handle unresitricted variables (set x to x1-x2)
        for (i = 0; i < unRestricted.size(); i++) {
            if (!unRestricted[i])
                continue;
            varIdx = addVariable();
            for (j = 0; j < nCon; j++)
                lhs[j][varIdx] = -lhs[j][i];
            of[varIdx] = -of[i];
            negativePart[i] = varIdx;
            positivePart[varIdx] = i;
            isNegativePart[varIdx] = true;
        }

//Standardize contstraints
        for (i = 0; i < nCon; i++) {
            if (rhs[i] < 0) {
                rhs[i] *= -1;
                for (j = 0; j < nVar; j++)
                    lhs[i][j] *= -1;
                if (constraintTypes[i] != EQ)
                    constraintTypes[i] = constraintTypes[i] == GE ? LE : GE; //modify GE to LE and vice versa
            }
//Add basic variable (variable in the initial solution, that is slack or artifical)
            int basicVar = addVariable();
            basic.push_back(basicVar);
            lhs[i][basicVar] = 1;
            switch (constraintTypes[i]) {
                case GE:
                    varIdx = addVariable(); //add surplus
                    lhs[i][varIdx] = -1;
                case EQ:
                    isArtificial[basicVar] = true;
                    of[basicVar] = -INF;
                    break;
            }
            constraintTypes[i] = EQ;
        }
    }
//Solve model using Simplex algorithm
    Result solve() {
//Standardize
        standardize();
//Solve
        int i, j, k;
        LD z, ratio, cmz;
        while (true) {
//Compute z, c-z and Select pivot column
            int pivotCol = 0;
            LD bestCMZ = -INF;
            for (j = 0; j < nVar; j++) {
                z = k = 0;
                for (i = 0; i < basic.size(); i++)
                    z += of[basic[i]] * lhs[k++][j];
                cmz = of[j] - z;
                pivotCol = (cmz > bestCMZ) ? j : pivotCol;
                bestCMZ = max(cmz, bestCMZ);
            }
//Check if no more improvement
            if (fabs(bestCMZ) < EPS)
                break;
//Compute ratio and Select pivot row
            int pivotRow = 0;
            LD bestRatio = INF;
            for (i = 0; i < nCon; i++) {
                if (lhs[i][pivotCol] < EPS)
                    continue; //avoid division by zero
                ratio = rhs[i] / lhs[i][pivotCol];
                if (ratio < 0)
                    ratio = INF; //to avoid selecting negative ratios
                pivotRow = ratio < bestRatio ? i :
                           pivotRow;
                bestRatio = min(bestRatio, ratio);
            }
            if (bestRatio >= INF)
                return UNBOUND; //unbounded solution (can achieve infinite profit)
//Update table
            basic[pivotRow] = pivotCol;
//Set coeff of new basic to 1
            LD pivot = lhs[pivotRow][pivotCol];
            for (i = 0; i < nVar; i++)
                lhs[pivotRow][i] /= pivot;
            rhs[pivotRow] /= pivot;
//Set coeff of pivotCol to 0
            for (i = 0; i < nCon; i++) {
                if (i == pivotRow)
                    continue;
                LD val = -lhs[i][pivotCol];
                for (j = 0; j < nVar; j++)
                    lhs[i][j] += lhs[pivotRow][j] * val;
                rhs[i] += rhs[pivotRow] * val;
            }
        }
        //Compute solution
        for (i = 0; i < basic.size(); i++) {
            if (isArtificial[basic[i]] && fabs(rhs[i]) > EPS)
                return UNFEASIBLE;
            if (basic[i] < solution.size())
                solution[basic[i]] += rhs[i];
            else if (isNegativePart[basic[i]])
                solution[positivePart[basic[i]]] += -
                        rhs[i];
        }
        return OK;
    }
/******Methods******/
};

void burn()
{
    int n, m; cin >> n >> m;
    SimplexModel model;
    model.oftype = MAX;

    // Constraints
    model.unRestricted.resize(m, false);
    model.constraintTypes.resize(n, LE);
    model.lhs.resize(n, vector<LD> (m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> model.lhs[i][j];
        }
    }

    // constants
    model.rhs.resize(n);
    for (auto &i : model.rhs) cin >> i;

    // function
    model.of.resize(m);
    for (auto &i : model.of) cin >> i;

    Result ans = model.solve();
    if (ans == UNFEASIBLE) cout << "NO";
    else if (ans == UNBOUND) cout << "INF";
    else {
        cout << fixed << setprecision(18);
        cout << "YES\n";
        for (auto &i : model.solution) cout << i << ' ';
    }
}

int main()
{
    AboTaha_on_da_code
    int t = 1; // cin >> t;

    for (int i = 1; i <= t; i++) {
//        cout << "Test " << i << ":\n";
        burn();
        cout << '\n';
    }
    return 0;
}
