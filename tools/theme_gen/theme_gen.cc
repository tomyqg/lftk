/**
 * File:   theme_gen.cc
 * Author: Li XianJing <xianjimli@hotmail.com>
 * Brief:  theme_gen interface
 *
 * Copyright (c) 2018 - 2018  Li XianJing <xianjimli@hotmail.com>
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * License file for more details.
 *
 */

/**
 * History:
 * ================================================================
 * 2018-01-14 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "theme_gen.h"
#include "base/theme.h"
#include "base/types_def.h"

Style::Style() {}

Style::Style(uint16_t type, uint8_t subtype, uint8_t state) {
  this->type = type;
  this->subtype = subtype;
  this->state = state;
}

Style::~Style() {}

bool Style::AddInt(uint32_t name, int32_t value) {
  this->int_values.push_back(NameIntValue(name, value));

  return true;
}

bool Style::AddString(uint32_t name, const string& value) {
  this->str_values.push_back(NameStringValue(name, value));

  return true;
}

uint8_t* Style::Output(uint8_t* buff, uint32_t max_size) {
  uint32_t size = 0;
  uint8_t* p = buff;
  uint8_t* end = buff + max_size;
  return_value_if_fail(buff != NULL && max_size > 32, NULL);

  size = this->int_values.size();
  save_uint32(p, size);
  printf("  size=%d type=%d subtype=%d state=%d\n", size, this->type, this->subtype, this->state);
  for (vector<NameIntValue>::iterator i = this->int_values.begin(); i != this->int_values.end();
       i++) {
    uint32_t name = i->name;
    uint32_t value = i->value;
    return_value_if_fail((end - p) > 8, NULL);

    save_uint32(p, name);
    save_uint32(p, value);
    printf("    %d=0x%08x\n", name, value);
  }

  return_value_if_fail((end - p) > 32, NULL);

  size = this->str_values.size();
  save_uint32(p, size);
  for (vector<NameStringValue>::iterator i = this->str_values.begin(); i != this->str_values.end();
       i++) {
    uint32_t name = i->name;
    string value = i->value;
    uint32_t s_size = value.size();
    return_value_if_fail((end - p) > s_size + 5, NULL);

    save_uint32(p, name);
    memcpy(p, value.c_str(), s_size + 1);
    p += s_size + 1;
    printf("    %d=%s\n", name, value.c_str());
  }

  return p;
}

bool ThemeGen::AddStyle(const Style& style) {
  this->styles.push_back(style);

  return true;
}

uint8_t* ThemeGen::Output(uint8_t* buff, uint32_t max_size) {
  uint8_t* p = buff;
  uint32_t version = 0x0;
  uint32_t size = this->styles.size();
  uint8_t* end = buff + max_size;

  return_value_if_fail(p != NULL && max_size > 128, NULL);

  save_uint32(p, THEME_MAGIC);
  save_uint32(p, version);
  save_uint32(p, size);

  uint8_t* index = p;
  p += size * 8;
  printf("size=%d\n", size);
  for (vector<Style>::iterator iter = this->styles.begin(); iter != this->styles.end(); iter++) {
    uint32_t v = (iter->type << 16) | (iter->subtype << 8) | iter->state;
    uint32_t offset = p - buff;
    save_uint32(index, v);
    save_uint32(index, offset);

    p = iter->Output(p, end - p);
  }

  return p;
}
