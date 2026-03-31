#include "note.hpp"
#include <stdexcept>

namespace ulanova
{
  void create_note(DB& db, const std::string& name)
  {
    db[name] = std::make_shared<Note>(Note{name});
  }
  void add_line(DB& db, const std::string& name, const std::string& text)
  {
    auto it = db.find(name);
    if (it == db.end())
    {
      throw std::logic_error("note not found");
    }
    it -> second -> lines.push_back(text);
  }
  std::vector<std::string> show(const DB& db, const std::string& name)
  {
    auto it = db.find(name);
    if (it == db.end())
    {
      throw std::logic_error("note not found");
    }
    return it->second->lines;
  }
}