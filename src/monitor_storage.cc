#include <monitor_storage.h>

namespace monitor {


Storage::Storage(std::chrono::seconds span)
: d_span(span), d_storage()
{}

std::size_t Storage::size() const
{
    return d_storage.size();
}

void Storage::add(LogRecord rec)
{
    std::chrono::seconds time_point (rec.date);
    d_storage.emplace(time_point, rec);
    maintain(time_point);
}

void Storage::maintain(std::chrono::seconds cur)
{
    std::chrono::seconds drop_point = cur - d_span;
    auto iter = d_storage.lower_bound(drop_point);
    if (iter!=d_storage.end())
        d_storage.erase(d_storage.begin(), iter);
}

Storage::iters_t Storage::find_out_of_span(std::chrono::seconds cur)
{
    if (d_storage.empty())
        return {d_storage.end(), d_storage.end()};
    std::chrono::seconds drop_point = cur - d_span;
    auto bound = d_storage.lower_bound(drop_point);
    return {d_storage.begin(), bound};
   
}

} // namespace monitor