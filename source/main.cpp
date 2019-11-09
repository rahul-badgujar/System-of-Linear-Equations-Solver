#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <map>
#include <string>

#define MATRIX vector<vector<float>>

using namespace std;

enum solutions
{
    NO_SOLUTIONS,
    UNIQUE_SOLUTION,
    INFINITE_SOLUTIONS
};

void rowInterchange(MATRIX &matrix, const int &r1, const int &r2)
{
    for (int i = 0; i < matrix[0].size(); i++)
    {
        std::swap(matrix[r1][i], matrix[r2][i]);
    }
}

void rowTransform(MATRIX &matrix, const int &r1, const int &r2, const int &e)
{
    int a = matrix[r1][e], b = matrix[r2][e];
    if (b != 0)
    {
        for (int i = 0; i < matrix[0].size(); i++)
        {
            matrix[r2][i] = (b * matrix[r1][i] - a * matrix[r2][i]);
        }
    }
}

MATRIX rowEchelon(const MATRIX &matrix)
{
    int iCur = 0, jCur = 0;
    MATRIX tempMatrix = matrix;
    for (iCur = 0; iCur < tempMatrix.size(); iCur++)
    {
        if (tempMatrix[iCur][jCur] == 0)
        {
            bool found = false;
            for (int t = iCur + 1; t < tempMatrix.size(); t++)
            {
                if (tempMatrix[t][jCur] != 0)
                {
                    found = true;
                    rowInterchange(tempMatrix, iCur, t);
                    break;
                }
            }
            if (!found)
            {
                jCur++;
                if (jCur >= tempMatrix[0].size())
                {
                    break;
                }
                iCur--;
                continue;
            }
        }
        for (int b = iCur + 1; b < tempMatrix.size(); b++)
        {
            rowTransform(tempMatrix, iCur, b, jCur);
        }
    }
    return tempMatrix;
}

enum solutions typeofSolution(const MATRIX &matrix)
{
    int rankA = matrix.size();
    int rankAB = rankA;
    for (int i = 0; i < matrix.size(); i++)
    {
        bool isNullRow = true;
        for (int j = 0; j < matrix[i].size() - 1; j++)
        {
            if (matrix[i][j] != 0)
            {
                isNullRow = false;
                break;
            }
        }
        if (isNullRow)
        {
            rankA--;
            if (matrix[i][matrix[i].size() - 1] == 0)
                rankAB--;
        }
    }
    cout << "Rank A : " << rankA << " , Rank AB : " << rankAB << endl;
    if (rankA != rankAB)
        return solutions::NO_SOLUTIONS;
    else
    {
        if (rankA == matrix.size())
            return solutions::UNIQUE_SOLUTION;
        else
            return solutions::INFINITE_SOLUTIONS;
    }
}

vector<float> getUniqueSolution(MATRIX &matrix)
{
    vector<float> v;
    int n = matrix.size() - 1, m = matrix[0].size() - 2;
    while (matrix[n][m] == 0 && n >= 0)
        n--;
    while (n >= 0 && m >= 0)
    {
        float value = matrix[n][matrix[0].size() - 1];
        for (int i = m + 1; i < matrix[0].size() - 1; i++)
            value -= (matrix[n][i]);
        value /= (matrix[n][m]);
        v.push_back(value);
        for (int i = n - 1; i >= 0; i--)
        {
            matrix[i][m] = (matrix[i][m]) * value;
        }
        n--;
        m--;
    }
    reverse(v.begin(), v.end());
    return v;
}

void printArr(const MATRIX &matrix)
{
    cout.setf(std::ios::left);
    for (auto i : matrix)
    {
        for (auto j : i)
        {

            cout << std::setw(7) << j;
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    int n = 3, m = 4;
    MATRIX matrix(n, vector<float>(m));
    matrix = {
        {1, -1, -1, 0},
        {1, 0, 2, 6},
        {0, 2, -1, 5}};
    printArr(matrix);
    MATRIX rowEchelonMat = rowEchelon(matrix);
    printArr(rowEchelonMat);
    enum solutions s = typeofSolution(rowEchelonMat);
    if (s == solutions::UNIQUE_SOLUTION)
    {
        cout << "Unique Solution exist for the System of Linear Equations" << endl;
        vector<float> solution = getUniqueSolution(matrix);
        for (auto i : solution)
            cout << i << "  ";
    }
    else if (s == solutions::INFINITE_SOLUTIONS)
    {
        cout << "Infinite Solutions exist for the System of Linear Equations" << endl;
    }
    else
    {
        cout << "No Solution exist for the System of Linear Equations" << endl;
    }
    cin.get();
    return 0;
}
