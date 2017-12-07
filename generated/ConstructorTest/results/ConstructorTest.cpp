#include <memory>
#include <fstream>
#include <vector>
#include <map>
#include <iostream>

class OneMapHelper {
  public:
    template<typename K, typename V> static std::shared_ptr<std::vector<K>> keys(const std::map<K,V>& map) {
        std::vector<K> result;
        for(auto it = map.begin(); it != map.end(); ++it)
            result.push_back(it->first);
        return std::make_shared<std::vector<K>>(result);
    }

    template<typename K, typename V> static std::shared_ptr<std::vector<V>> values(const std::map<K,V>& map) {
        std::vector<V> result;
        for(auto it = map.begin(); it != map.end(); ++it)
            result.push_back(it->second);
        return std::make_shared<std::vector<V>>(result);
    }
};

class OneStringHelper {
  public:
    static std::shared_ptr<std::vector<std::string>> split(const std::string& str, const std::string& delim)
    {
        std::vector<std::string> tokens;
        
        size_t prev = 0, pos = 0;
        do
        {
            pos = str.find(delim, prev);
            if (pos == std::string::npos) pos = str.length();
            std::string token = str.substr(prev, pos - prev);
            tokens.push_back(token);
            prev = pos + delim.length();
        }
        while (pos < str.length() && prev < str.length());

        return std::make_shared<std::vector<std::string>>(tokens);
    }
};

class OneFile {
  public:
    static std::string readText(const std::string& path)
    {
      std::ifstream file(path);
      std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
      return content;
    }
};

class ConstructorTest {
  public:
    int field2;
    int field1;

    ConstructorTest(int field1) {
        this->field1 = field1;
        this->field2 = field1 * this->field1 * 5;
    }

  private:
};

class TestClass {
  public:
    void testMethod() {
        auto test = std::make_shared<ConstructorTest>(3);
        std::cout << (test->field2) << std::endl;
    }

  private:
};

int main()
{
    TestClass c;
    c.testMethod();
    return 0;
}