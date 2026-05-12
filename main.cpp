#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

struct StudySession {
    string subject;
    int duration;               // minutes
    int focusLevel;             // 1–5
    int difficulty;             // 1–5
    double productivityScore;
};

vector<StudySession> sessions;


// PRODUCTIVITY CALCULATION
double calculateProductivity(int duration, int focus, int difficulty) {
    return (duration * focus) / (double)difficulty;
}


// RESULT LABEL
string getResult(double score) {
    if (score >= 90)
        return "Excellent";
    else if (score >= 70)
        return "Good";
    else if (score >= 40)
        return "Average";
    else
        return "Needs Improvement";
}


// ADVICE
string getAdvice(double score) {
    if (score >= 80)
        return "Excellent focus! Keep it up and challenge yourself.";

    else if (score >= 70)
        return "Good work. Improve focus or extend study time.";

    else if (score >= 40)
        return "Average. Reduce distractions and stay consistent.";

    else
        return "Needs improvement. Use shorter sessions and take breaks.";
}


// ADD SESSION
void addSession() {
    StudySession s;
    int timeChoice;

    cout << "\n--- ADD STUDY SESSION ---\n";

    cout << "Enter subject: ";
    cin.ignore();
    getline(cin, s.subject);

    cout << "\nSelect study time:\n";
    cout << "1. 25 minutes\n";
    cout << "2. 45 minutes\n";
    cout << "3. 60 minutes\n";
    cout << "Enter choice: ";
    cin >> timeChoice;

    switch (timeChoice) {
        case 1: s.duration = 25; break;
        case 2: s.duration = 45; break;
        case 3: s.duration = 60; break;

        default:
            cout << "Invalid choice! Defaulting to 25 minutes.\n";
            s.duration = 25;
    }

    cout << "Enter focus level (1-5): ";
    cin >> s.focusLevel;

    cout << "Enter difficulty level (1-5): ";
    cin >> s.difficulty;

    s.productivityScore =
        calculateProductivity(
            s.duration,
            s.focusLevel,
            s.difficulty
        );

    sessions.push_back(s);

    cout << "\nSession added successfully!\n";
}


// SHOW RECORDS
void showSessions() {
    if (sessions.empty()) {
        cout << "\nNo sessions recorded.\n";
        return;
    }

    cout << "\n--- STUDY RECORDS ---\n";

    cout << left
         << setw(15) << "Subject"
         << setw(10) << "Time"
         << setw(10) << "Focus"
         << setw(16) << "Difficulty"
         << setw(12) << "Score"
         << setw(20) << "Result"
         << endl;

    cout << string(80, '-') << endl;

    for (auto &s : sessions) {
        cout << setw(15) << s.subject
             << setw(10) << s.duration
             << setw(10) << s.focusLevel
             << setw(16) << s.difficulty
             << setw(12) << fixed << setprecision(2)
             << s.productivityScore
             << setw(20) << getResult(s.productivityScore)
             << endl;
    }
}


// ANALYZE ALL
void analyzeAll() {
    if (sessions.empty()) {
        cout << "\nNo data to analyze.\n";
        return;
    }

    double totalTime = 0;
    double totalScore = 0;

    for (auto &s : sessions) {
        totalTime += s.duration;
        totalScore += s.productivityScore;
    }

    double avg = totalScore / sessions.size();

    auto best = max_element(
        sessions.begin(),
        sessions.end(),
        [](StudySession a, StudySession b) {
            return a.productivityScore < b.productivityScore;
        });

    cout << "\n--- ANALYSIS (ALL SUBJECTS) ---\n";

    cout << "Total Study Time: "
         << totalTime
         << " minutes\n";

    cout << "Average Productivity: "
         << fixed << setprecision(2)
         << avg << endl;

    cout << "Performance Result: "
         << getResult(avg) << endl;

    cout << "Advice: "
         << getAdvice(avg) << endl;

    cout << "Best Subject: "
         << best->subject
         << " (" << best->productivityScore << ")\n";
}


// ANALYZE ONE SUBJECT
void analyzeOneSubject() {
    if (sessions.empty()) {
        cout << "\nNo data to analyze.\n";
        return;
    }

    string search;

    cout << "\nEnter subject to analyze: ";
    cin.ignore();
    getline(cin, search);

    double totalTime = 0;
    double totalScore = 0;
    int count = 0;

    StudySession best;
    bool found = false;

    for (auto &s : sessions) {
        if (s.subject.find(search) != string::npos) {

            totalTime += s.duration;
            totalScore += s.productivityScore;

            if (!found ||
                s.productivityScore > best.productivityScore) {

                best = s;
                found = true;
            }

            count++;
        }
    }

    if (count == 0) {
        cout << "\nNo matching subject found.\n";
        return;
    }

    double avg = totalScore / count;

    cout << "\n--- ANALYSIS (SUBJECT: "
         << search << ") ---\n";

    cout << "Sessions Found: "
         << count << endl;

    cout << "Total Time: "
         << totalTime
         << " minutes\n";

    cout << "Average Productivity: "
         << fixed << setprecision(2)
         << avg << endl;

    cout << "Performance Result: "
         << getResult(avg) << endl;

    cout << "Advice: "
         << getAdvice(avg) << endl;

    cout << "Best Session Score: "
         << best.subject
         << " (" << best.productivityScore << ")\n";
}


// ANALYZE MENU
void analyze() {
    if (sessions.empty()) {
        cout << "\nNo data to analyze.\n";
        return;
    }

    int choice;

    cout << "\n--- ANALYZE MENU ---\n";
    cout << "1. Analyze All Subjects\n";
    cout << "2. Analyze One Subject\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {

        case 1:
            analyzeAll();
            break;

        case 2:
            analyzeOneSubject();
            break;

        default:
            cout << "Invalid choice!\n";
    }
}


// MAIN
int main() {
    int choice;

    do {
        cout << "\n===== STUDY SESSION PRODUCTIVITY ANALYZER =====\n";

        cout << "1. Add Session\n";
        cout << "2. Show Records\n";
        cout << "3. Analyze\n";
        cout << "4. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                addSession();
                break;

            case 2:
                showSessions();
                break;

            case 3:
                analyze();
                break;

            case 4:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 4);

    return 0;
}
