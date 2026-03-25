//#include <cpr/cpr.h>
//#include <iostream>
//#include <nlohmann/json.hpp>
//
//
//using json = nlohmann::json;
//
//int main() {
//    auto response = cpr::Post(
//        cpr::Url{ "https://abcd97.openai.azure.com/openai/deployments/gpt-4.1-mini/chat/completions?api-version=2024-06-01" },
//        cpr::Header{
//            {"Content-Type", "application/json"},
//            {"api-key", "your_api_key_here"}
//        },
//        cpr::Body{ R"({
//  "messages": [
//    {
//      "role": "system",
//      "content": "You are a student performance analyst. Analyze the students and provide clear insights. Focus on patterns, strengths, weaknesses, and suggestions. Use the given weights (grade: 0.5, attendance: 0.3, projectScore: 0.2) as a guide for evaluation. Respond in natural language with structured insights. Be concise but insightful."
//    },
//    {
//      "role": "user",
//      "content": "[{\"name\":\"Ali\",\"grade\":95,\"attendance\":90,\"projectScore\":88},{\"name\":\"Sara\",\"grade\":70,\"attendance\":75,\"projectScore\":72},{\"name\":\"Omar\",\"grade\":40,\"attendance\":50,\"projectScore\":45},{\"name\":\"Lina\",\"grade\":60,\"attendance\":80,\"projectScore\":55},{\"name\":\"Ahmed\",\"grade\":85,\"attendance\":70,\"projectScore\":65}]"
//    }
//  ],
//  "max_tokens": 2000,
//  "temperature": 0.8
//})" }
//);
//
//    // Print response
//    std::cout << "Body: " << response.text << std::endl;
//
//    system("pause>0");
//    return 0;
//}