#include<iostream>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include<string>
using namespace std;
using json = nlohmann::json;

struct Student {
    string name;
    double grade;
    double attendance;
    double projectScore;
};

int main() {

    vector<Student> students = {
        {"Ali",   95, 90, 88},
        {"Sara",  70, 75, 72},
        {"Omar",  40, 50, 45},
        {"Lina",  60, 80, 55},
        {"Ahmed", 85, 70, 65}
    };

    cout << "==============================\n";
    cout << "===  Deterministic\n";
    cout << "==============================\n";

    for (const auto& s : students) {
        double score = s.grade * 0.5 + s.attendance * 0.3 + s.projectScore * 0.2;

        string cluster;
        if (score >= 80) cluster = "High";
        else if (score >= 60) cluster = "Medium";
        else                  cluster = "Low";

        cout << s.name << ":\n";
        cout << "  Score: " << score << "\n";
        cout << "  Cluster: " << cluster << "\n\n";
    }

    cout << "==============================\n";
    cout << "===  Probabilistic\n";
    cout << "==============================\n";

    // Build JSON array from students vector
    json studentArray = json::array();
    for (const auto& s : students) {
        studentArray.push_back({
            {"name",         s.name},
            {"grade",        s.grade},
            {"attendance",   s.attendance},
            {"projectScore", s.projectScore}
            });
    }

    // Build request body
    json body = {
        {"messages", {
            {{"role", "system"}, {"content", "You are a student performance analyst. Analyze the students using weights (grade: 0.5, attendance: 0.3, projectScore: 0.2). Return ONLY a valid JSON object. Do NOT include explanations, text, or markdown. Output must strictly follow this format:\n{\n  \"students\": [\n    {\"name\": \"string\", \"analysis\": \"string\"}\n  ],\n  \"summary\": \"string\"\n}"}},
            {{"role", "user"},   {"content", studentArray.dump()}}
        }},
        {"max_tokens", 500},
        {"temperature", 0.8}
    };

    auto response = cpr::Post(
        cpr::Url{ "https://abcd97.openai.azure.com/openai/deployments/gpt-4.1-mini/chat/completions?api-version=2024-06-01" },
        cpr::Header{ {"Content-Type", "application/json"}, {"api-key", "your_api_key_here"} },
        cpr::Body{ body.dump() }
    );

    json full = json::parse(response.text);
    string content = full["choices"][0]["message"]["content"];
    json report = json::parse(content);

    for (const auto& student : report["students"]) {
        cout << student["name"] << ":\n";
        cout << student["analysis"] << "\n\n";
    }
    cout << "Summary:\n" << report["summary"] << "\n";

    system("pause>0");
    return 0;
}