#include <iostream>
#include <algorithm>
#include <numeric>
#include <math.h>
using namespace std;

int main()
{
    const int size = 5;
    int quota = 100; // Total amount to allocate
    float weights[size];
    int scoreList[size];
    float remainderList[size];
    float totalWeight = 0.0;
    int totalScore = 0;

    cout << "Insert quota: ";
    cin >> quota;

    cout << "Insert weights: \n";
    // Request user input for weights
    for (int i = 0; i < size; i++)
    {
        cin >> weights[i];
    }

    // Lambda function to invert weights in the case of negative quota
    auto invert = [](float &element)
    { element = 1 / element; };
    if (quota < 0)
    {
        for_each(begin(weights), end(weights), invert);
    }

    // Calculate weights total
    totalWeight = accumulate(begin(weights), end(weights), 0.0);

    // Calculate scores and remainders
    cout << "\nScores: \n";
    for (int i = 0; i < size; i++)
    {
        float real_score = float(weights[i]) / totalWeight * float(quota);
        int score;
        float remainder;
        // Round down and store remainders
        if (quota >= 0)
        {
            score = floor(real_score);
            remainder = real_score - score;
        }
        else
        {
            score = ceil(real_score);
            remainder = score - real_score;
        }
        totalScore += score;
        scoreList[i] = score;
        remainderList[i] = remainder;
        cout << score << ", Remainder: " << remainder << "\n";
    }

    // Calculate total remainder
    int totalRemainder;
    if (quota >= 0)
    {
        totalRemainder = quota - totalScore;
    }
    else
    {
        totalRemainder = totalScore - quota;
    }

    // Adjust scores based on remainders
    for (int i = 0; i < totalRemainder; i++)
    {
        float highestRemainder = 0.0;
        int selectedIndex = 0;
        // Select score with the highest remainder
        for (int j = 0; j < size; j++)
        {
            if (remainderList[j] > highestRemainder)
            {
                highestRemainder = remainderList[j];
                selectedIndex = j;
            }
        }
        // Adjust selected score
        if (quota >= 0)
        {
            scoreList[selectedIndex] += 1;
        }
        else
        {
            scoreList[selectedIndex] -= 1;
        }
        remainderList[selectedIndex] = 0; // Set remainder to 0 after adjustment
    }
    
    // Display final scores
    cout << "\nFinal Scores: \n";
    for (int i = 0; i < size; i++)
    {
        cout << i + 1 << ". " << scoreList[i] << "\n";
    }
    
    return 0;
}