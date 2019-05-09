#include <string>

std::string parseJson(std::string j)
{
	 std::string original = "\"original\":{\"url\":\"";
    int start = j.find(original);
    int end = j.find(".gif", start + 1);
    int len = end - start + 4 - original.length();
    j = j.substr(start + original.length(),len);
    std::string url = "";
    for (int i = 0; i < j.length(); ++i) {
    if (j[i] != '\\')
      url += j[i];
    }
    return url;
}
