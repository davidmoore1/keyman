/*
  Copyright:    © SIL International.
  Description:  Internal keyboard class and adaptor class for the LDML Keyboard Processor.
  Create Date:  6 Aug 2022
  Authors:      Marc Durdin
*/

#pragma once

#include <map>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <memory>
#include <keyman/keyman_core_api.h>
#include "processor.hpp"
#include "option.hpp"
#include "ldml_vkeys.hpp"
#include "ldml_transforms.hpp"

namespace km {
namespace core {

#define KM_CORE_LMDL_PROCESSOR_VERSION u"1.0"

  class ldml_processor : public abstract_processor {
  private:
    bool _valid;
    std::unique_ptr<ldml::transforms> transforms, bksp_transforms;
    ldml::vkeys keys;
  public:
    ldml_processor(
      path const & kb_path,
      const std::vector<uint8_t> & data
    );

//    ~ldml_processor() override;

    static bool is_kmxplus_file(
      path const & kb_path,
      std::vector<uint8_t>& data
    );

    km_core_status
    process_event(
      km_core_state *state,
      km_core_virtual_key vk,
      uint16_t modifier_state,
      uint8_t is_key_down,
      uint16_t event_flags
    ) override;

    virtual km_core_attr const & attributes() const override;
    km_core_status               validate() const override;

    char16_t const *
    lookup_option(
      km_core_option_scope _kmn_unused(scope),
      std::u16string const & _kmn_unused(key)
    ) const override {
      return nullptr;
    }

    option
    update_option(
      km_core_option_scope _kmn_unused(scope),
      std::u16string const & _kmn_unused(key),
      std::u16string const & _kmn_unused(value)
    ) override {
      return option();
    }

    km_core_status process_queued_actions(km_core_state *state) override;

    bool queue_action(
      km_core_state * state,
      km_core_action_item const* action_item
    ) override;

    km_core_context_item * get_intermediate_context() override;

    km_core_keyboard_key  * get_key_list() const override;

    km_core_keyboard_imx  * get_imx_list() const override;

  private:
     /** emit text to context and actions */
     static void emit_text(km_core_state *state, const std::u16string &str);
     /** emit text to context and actions */
     static void emit_text(km_core_state *state, const std::u32string &str);
     /** emit char to context and actions */
     static void emit_text(km_core_state *state, km_core_usv ch);
     /** emit a marker */
     static void emit_marker(km_core_state *state, KMX_DWORD marker);
     /**
      * Delete text from the state.
      * @param str string with text to remove, from the end
      * @param length number of chars from the end of str to drop
      */
     static void remove_text(km_core_state *state, std::u32string &str, size_t length);

     /** process a typed key */
     void process_key_string(km_core_state *state, const std::u16string &key_str) const;

     /**
      * add the string+marker portion of the context to the beginning of str.
      * Stop when a non-string and non-marker is hit.
      * Convert markers into the UC_SENTINEL format.
      * @return the number of context items consumed
      */
     static size_t context_to_string(km_core_state *state, std::u32string &str, bool include_markers = true);

     /** prepend the marker string in UC_SENTINEL format to the str */
     inline static void prepend_marker(std::u32string &str, KMX_DWORD marker);
  };

  void
  ldml_processor::prepend_marker(std::u32string &str, KMX_DWORD marker) {
     km_core_usv triple[] = {LDML_UC_SENTINEL, LDML_MARKER_CODE, marker};
     str.insert(0, triple, 3);
  }

} // namespace core
} // namespace km