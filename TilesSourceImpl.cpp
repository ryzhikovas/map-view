#include "TilesSourceImpl.hpp"
#include <fstream>

namespace {
    constexpr char separator = '/';
}

TilesSourceImpl::TilesSourceImpl(std::string dir)
    : dataDirectory{std::move(dir)} {
    if (dataDirectory.empty() || dataDirectory.back() != separator) {
        dataDirectory.push_back(separator);
    }
}

std::optional<TileData> TilesSourceImpl::get(const TileId& id) const {
    std::string path = dataDirectory;
    path += std::to_string(id.level) + "_";
    path += std::to_string(id.pos.y) + "_";
    path += std::to_string(id.pos.x) + ".raw";
    std::ifstream file(path, std::ios::binary);
    std::vector<char> buffer(255 * 255 * 3);
    file.read(buffer.data(), buffer.size());
    return file.good() ? std::make_optional(buffer) : std::nullopt;
}

std::string TilesSourceImpl::name() const {
    return "tiles source stub";
}
