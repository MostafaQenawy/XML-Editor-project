#include "postsearch.h"

std::string getTopicBodyFromString(const std::string& xmlContent, const std::string& topicName) {
    size_t topicStart = xmlContent.find(">" + topicName + "<");
    if (topicStart == std::string::npos) {
        return "";
    }

    size_t precedingBodyStart = xmlContent.rfind("<body>", topicStart);
    if (precedingBodyStart == std::string::npos) {
        return "";
    }

    size_t bodyStart = xmlContent.find("<body>", precedingBodyStart);
    if (bodyStart == std::string::npos) {
        return "";
    }

    size_t bodyEnd = xmlContent.find("</body>", bodyStart);
    if (bodyEnd == std::string::npos) {
        return "";
    }

    return xmlContent.substr(bodyStart + 6, bodyEnd - (bodyStart + 6));
}
