#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include <regex>
#include <cctype>
#include <map>
#include <vector>
#include <algorithm>

#if defined(WITH_GTEST)
#include <gtest/gtest.h>
#endif

enum Level {
    Even,
    Light,
    Heavy,
};

class Counterfeit
{
    // constructions
public:
    explicit Counterfeit(std::istream &is);

    // methods
public:
    void show();
    std::string check(void);
    void parser_coin(std::string &input);

    // data
private:
    std::map< std::string, int > even_coin_;
    std::map< std::string, int > light_coin_;
    std::map< std::string, int > heavy_coin_;
    std::vector< std::string > light_coin_group_;
    std::vector< std::string > heavy_coin_group_;
};

Counterfeit::Counterfeit(std::istream &is)
{
    even_coin_.clear();
    light_coin_.clear();
    heavy_coin_.clear();
    light_coin_group_.clear();
    heavy_coin_group_.clear();
    for (int i = 0; i < 3; i++) {
        std::string input;
        std::getline(is, input);
        //		std::cout << "input: " << input << std::endl;
        parser_coin(input);
    }
}

void Counterfeit::parser_coin(std::string &input)
{
    std::stringstream ss(input);
    std::string token1;
    std::string token2;
    std::string element;
    std::getline(ss, token1, ' ');
    std::getline(ss, token2, ' ');
    std::getline(ss, element, ' ');
    if (element.compare("even") == 0) {
        for (int i = 0; i < token1.length(); i++) {
            std::string ch = token1.substr(i, 1);
            even_coin_[ch] = Level::Even;
        }
        for (int i = 0; i < token2.length(); i++) {
            std::string ch = token2.substr(i, 1);
            even_coin_[ch] = Level::Even;
        }
    } else if (element.compare("up") == 0) {
        heavy_coin_group_.push_back(token1);
        for (int i = 0; i < token1.length(); i++) {
            std::string ch = token1.substr(i, 1);
            heavy_coin_[ch] = Level::Heavy;
        }
        light_coin_group_.push_back(token2);
        for (int i = 0; i < token2.length(); i++) {
            std::string ch = token2.substr(i, 1);
            light_coin_[ch] = Level::Light;
        }
    } else if (element.compare("down") == 0) {
        light_coin_group_.push_back(token1);
        for (int i = 0; i < token1.length(); i++) {
            std::string ch = token1.substr(i, 1);
            light_coin_[ch] = Level::Light;
        }
        heavy_coin_group_.push_back(token2);
        for (int i = 0; i < token2.length(); i++) {
            std::string ch = token2.substr(i, 1);
            heavy_coin_[ch] = Level::Heavy;
        }
    }
}

void Counterfeit::show(void)
{
    std::cout << "even_coin_ : " << std::endl;
    for (auto &it : even_coin_)
        std::cout << it.first << " ";
    std::cout << std::endl;
    std::cout << "up_coin_ : " << std::endl;
    for (auto &it : light_coin_group_)
        std::cout << it << " ";
    std::cout << std::endl;
    std::cout << "down_coin_ : " << std::endl;
    for (auto &it : heavy_coin_group_)
        std::cout << it << " ";
    std::cout << std::endl;
}

std::string Counterfeit::check(void)
{
    std::string out(" is the counterfeit coin and it is ");

    // 1. remove even coin
    for (int i = 0; i < light_coin_group_.size(); i++) {
        for (auto &it : even_coin_) {
            std::size_t found = light_coin_group_[i].find(it.first);
            if (found != std::string::npos)
                light_coin_group_[i].erase(found, 1);
        }
        if (light_coin_group_[i].length() == 0)
            light_coin_group_.erase(light_coin_group_.begin() + i);
    }
    for (int i = 0; i < heavy_coin_group_.size(); i++) {
        for (auto &it : even_coin_) {
            std::size_t found = heavy_coin_group_[i].find(it.first);
            if (found != std::string::npos)
                heavy_coin_group_[i].erase(found, 1);
        }
        if (heavy_coin_group_[i].length() == 0)
            heavy_coin_group_.erase(heavy_coin_group_.begin() + i);
    }
    if ((light_coin_group_.size() == 1) && (heavy_coin_group_.size() == 0)) {
        out = light_coin_group_[0] + out + "light.";
        return out;
    }
    if ((light_coin_group_.size() == 0) && (heavy_coin_group_.size() == 1)) {
        out = heavy_coin_group_[0] + out + "heavy.";
        return out;
    }

    //2. remove coin on light/heavy group at same time
    for (int i = 0; i < light_coin_group_.size(); i++) {
        for (auto &it : heavy_coin_) {
            std::size_t found = light_coin_group_[i].find(it.first);
            if (found != std::string::npos)
                light_coin_group_[i].erase(found, 1);
        }
    }
    for (int i = 0; i < heavy_coin_group_.size(); i++) {
        for (auto &it : light_coin_) {
            std::size_t found = heavy_coin_group_[i].find(it.first);
            if (found != std::string::npos)
                heavy_coin_group_[i].erase(found, 1);
        }
    }
    std::map< std::string, int > coin_map;
    for (int i = 0; i < light_coin_group_.size(); i++) {
        if (light_coin_group_[i].length() == 1) {
            if (heavy_coin_group_[i].length() == 0) {
                out = light_coin_group_[i] + out + "light.";
                return out;
            }
            if (coin_map.count(light_coin_group_[i])) {
                out = light_coin_group_[i] + out + "light.";
                return out;
            }
            coin_map[light_coin_group_[i]] = 1;
            continue;
        }
        for (char c : light_coin_group_[i]) {
            std::string tmp_string;
            tmp_string.push_back(c);
            if (coin_map.count(tmp_string)) {
                coin_map[tmp_string]++;
            }
        }
    }
    for (auto &it : coin_map) {
        if (it.second == 3) {
            out = it.first + out + "light.";
            return out;
        }
    }
    coin_map.clear();
    for (int i = 0; i < heavy_coin_group_.size(); i++) {
        if (heavy_coin_group_[i].length() == 1) {
            if (light_coin_group_[i].length() == 0) {
                out = heavy_coin_group_[i] + out + "heavy.";
                return out;
            }
            if (coin_map.count(heavy_coin_group_[i])) {
                out = heavy_coin_group_[i] + out + "heavy.";
                return out;
            }
            coin_map[heavy_coin_group_[i]] = 1;
            continue;
        }
        for (char c : heavy_coin_group_[i]) {
            std::string tmp_string;
            tmp_string.push_back(c);
            if (coin_map.count(tmp_string)) {
                coin_map[tmp_string]++;
            }
        }
    }
    for (auto &it : coin_map) {
        if (it.second == 3) {
            out = it.first + out + "heavy.";
            return out;
        }
    }
	out.clear();
    return out;
}

void solve_uva_problem(std::istream &is, std::ostream &os)
{
    std::string input;
    std::getline(is, input);
    int counterfeit_num = stoi(input);
    while (counterfeit_num > 0) {
        Counterfeit counterfeit(is);
        os << counterfeit.check() << std::endl;
        //	counterfeit.show();
        counterfeit_num = counterfeit_num - 1;
    }
}

int main(int argc, char **argv)
{
#if !defined(WITH_GTEST)
    solve_uva_problem(std::cin, std::cout);
#else
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#endif
}
