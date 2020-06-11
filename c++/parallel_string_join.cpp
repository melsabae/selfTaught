#include <vector>
#include <string>
#include <numeric>
#include <iostream>
#include <tuple>
#include <algorithm>
#include <execution>
#include <functional>
#include <cstring>
#include <chrono>


using std::tuple;
using std::vector;
using std::string;


const auto policy = std::execution::par_unseq;


void parallel_string_copy(char* dst, const char* src)
{
  vector<size_t> indices(strlen(src));
  std::iota(indices.begin(), indices.end(), 0);

  std::for_each(policy, indices.cbegin(), indices.cend(),
      [&dst, &src](const size_t i) {
        dst[i] = src[i];
      });
}


std::string parallel_string_join2(char* buffer, const vector<string>& data, const string& delimiter)
{
  //const string newline = "\n";
  const string newline = "";
  const size_t newline_space = newline.size();
  const size_t delimiter_size = delimiter.size();
  const size_t delimiter_space = (data.size() - 1) * delimiter_size;

  vector<size_t> indices(data.size());
  vector<size_t> data_sizes(data.size());
  vector<size_t> offsets(data.size());
  vector<tuple<size_t, const char*, size_t>> ops(2 * data.size());

  std::iota(indices.begin(), indices.end(), 0);

  std::for_each(policy, indices.cbegin(), indices.cend(),
      [&offsets, &data_sizes, &ops, &delimiter, &delimiter_size, &data](const size_t i){
        data_sizes[i] = data[i].length();
        offsets[i] = std::accumulate(data_sizes.cbegin(), data_sizes.cbegin() + i, 0) + i;
        ops[i] = std::make_tuple(offsets[i], (data.cbegin() + i)->c_str(), data_sizes[i]);
        ops[offsets.size() + i] = std::make_tuple(offsets[i] + data_sizes[i], delimiter.c_str(), delimiter_size);
      });

  const size_t data_space = std::accumulate(data_sizes.cbegin(), data_sizes.cend(), 0);
  const size_t buffer_space = data_space + delimiter_space + newline_space + 1;

  ops[ops.size() - 1] = std::make_tuple(buffer_space - newline_space, newline.c_str(), newline_space);

  std::for_each(policy, ops.cbegin(), ops.cend(),
    [&buffer](const tuple<size_t, const char*, size_t>& t) {
      parallel_string_copy(buffer + std::get<0>(t), std::get<1>(t));
    });

  return string(buffer, buffer_space);
}


std::string parallel_string_join(char* buffer, const vector<string>& data, const string& delimiter)
{
  const size_t data_size = data.size();
  //const string newline = "\n";
  const string newline = "";
  const size_t newline_space = newline.size();
  const size_t delimiter_size = delimiter.size();
  const size_t delimiter_space = (data_size - 1) * delimiter_size;

  vector<size_t> indices(data.size());

  vector<size_t> data_sizes(data.size());
  vector<size_t> offsets(data.size());
  vector<tuple<size_t, const char*, size_t>> ops(2 * data.size());

  std::iota(indices.begin(), indices.end(), 0);

  std::for_each(policy, indices.cbegin(), indices.cend(),
      [&offsets, &data_sizes, &ops, &delimiter, &delimiter_size, &data](const size_t i){
        data_sizes[i] = data[i].length();
        offsets[i] = std::accumulate(data_sizes.cbegin(), data_sizes.cbegin() + i, 0) + i;
        ops[i] = std::make_tuple(offsets[i], (data.cbegin() + i)->c_str(), data_sizes[i]);
        ops[offsets.size() + i] = std::make_tuple(offsets[i] + data_sizes[i], delimiter.c_str(), delimiter_size);
      });

  const size_t data_space = std::accumulate(data_sizes.cbegin(), data_sizes.cend(), 0);
  const size_t buffer_space = data_space + delimiter_space + newline_space + 1;


  ops[ops.size() - 1] = std::make_tuple(buffer_space - newline_space, newline.c_str(), newline_space);


  std::for_each(policy, ops.cbegin(), ops.cend(),
    [&buffer](const tuple<size_t, const char*, size_t>& t) {
      memcpy(buffer + std::get<0>(t), std::get<1>(t), std::get<2>(t));
    });

  return string(buffer, buffer_space);
}

int main(int argc, char** argv)
{
  const vector<string> data =
  {
      "hey"
    , "there"
    , "amigo"
    , "ahoy"
    , "matey!"
  };

  const string delimiter = ",";
  char buffer[30] = { '.' };
  memset(buffer, '.', sizeof(buffer));

  std::function<string(char*, const vector<string>&, const string&)> f =
    argc > 1
    ? parallel_string_join2
    : parallel_string_join
    ;

  const string joined = f(buffer, data, delimiter);

  std::cout << joined << std::endl;

  return 0;
  (void) argc;
  (void) argv;
}
