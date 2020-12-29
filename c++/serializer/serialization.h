#ifndef __SERIALIZATION_H__
# define __SERIALIZATION_H__


#define SERIALIZED(x) serialized_ ## x
#define DESERIALIZED(x) x

#define SERIALIZATION(name) \
  void serialize_ ## name(SERIALIZED(name)* const output, const DESERIALIZED(name)* const input)

#define DESERIALIZATION(name) \
  void deserialize_ ## name(DESERIALIZED(name)* const output, const SERIALIZED(name)* const input)

#define DECLARE_SERIALIZATION(struct_name, struct_def) \
  typedef struct struct_def DESERIALIZED(struct_name); \
  typedef struct __attribute__((packed)) struct_def SERIALIZED(struct_name); \
  SERIALIZATION(struct_name); \
  DESERIALIZATION(struct_name);

#endif // __SERIALIZATION_H__
