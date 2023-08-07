#include <httplib.h>
#include <iostream>
#include <regex>

// Request configurations.
const std::string DOG_FACTS_ENDPOINT{"https://dog-api.kinduff.com"};
const std::string DOG_FACTS_ENDPOINT_PATH{"/api/facts"};
const httplib::Params DOG_FACTS_PARAMETERS{{"number", "1"}};
const httplib::Headers DOG_FACTS_HEADER{};

// Messages
const std::string DOG_FACTS_ERROR_MESSAGE{
        "Sorry, dog facts not available.\n"
        "Ensure you are connected to internet and try again :(."
    };
const std::string DOG_FACTS_INTRO_MESSAGE{"Here is a fact about dogs:\n"};

// response parsing util
const std::regex PATTERN{R"(\[(.*)\])"};

// parses the body of the returned response to fetch the fact.
void parse_response_body(const std::string& body)
{
    std::smatch fact_match;
    if (std::regex_search(body, fact_match, PATTERN)) {
        std::cout << '\t' << fact_match.str() << '\n';
    }
}

// Sends a request to DOG_FACTS_ENDPOINT, prints the fact
// returned by the server, or error messages in case of
// error.
void generate_dog_fact()
{
    httplib::Client dog_fact_client{DOG_FACTS_ENDPOINT};

    const httplib::Result response = dog_fact_client.Get(
                                DOG_FACTS_ENDPOINT_PATH,
                                DOG_FACTS_PARAMETERS,
                                DOG_FACTS_HEADER
                            );

    dog_fact_client.set_follow_location(true);  // helps to handle cases where the server
                                                // re-routes the endpoint.

    if (response) {
        switch (response->status) {
            case 200:
                std::cout << DOG_FACTS_INTRO_MESSAGE << '\n';
                parse_response_body(response->body);
                break;
            default:
                std::cerr << DOG_FACTS_ERROR_MESSAGE << '\n';
                std::cerr << "HTTP error: " << response->status << ' '
                            << httplib::to_string(response.error()) << '\n';
                break;
        }
    } else {
        std::cerr << DOG_FACTS_ERROR_MESSAGE << '\n';
        std::cerr << "HTTP error: " << httplib::to_string(response.error()) << '\n';
    }
}

int main()
{
    generate_dog_fact();
}
