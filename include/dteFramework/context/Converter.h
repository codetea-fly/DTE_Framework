#pragma once
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <functional>
#include <dteFramework/defs.h>

using json = nlohmann::json;

class DTEFramework_API JsonConverter {
public:
    using ConversionRule = std::function<void(const json&, json&)>;

    JsonConverter& add_rule(ConversionRule rule) {
        rules_.emplace_back(std::move(rule));
        return *this;
    }

    json convert(const json& source) const {
        json target;
        for (const auto& rule : rules_) {
            rule(source, target);
        }
        return target;
    }

    // 常用规则工厂方法
    static ConversionRule rename_field(const std::string& src_path,
        const std::string& dst_path) {
        return [=](const json& s, json& t) {
            if (s.contains(json::json_pointer(src_path))) {
                t[json::json_pointer(dst_path)] =
                    s[json::json_pointer(src_path)];
            }
            };
    }

    static ConversionRule transform_field(
        const std::string& src_path,
        const std::string& dst_path,
        std::function<json(const json&)> transformer) {
        return [=](const json& s, json& t) {
            if (s.contains(json::json_pointer(src_path))) {
                t[json::json_pointer(dst_path)] =
                    transformer(s[json::json_pointer(src_path)]);
            }
            };
    }

    static ConversionRule constant_field(const std::string& dst_path,
        const json& value) {
        return [=](const json&, json& t) {
            t[json::json_pointer(dst_path)] = value;
            };
    }

private:
    std::vector<ConversionRule> rules_;
};

//// 示例使用
//int main() {
//    // 示例源JSON结构
//    json source = {
//        {"personal", {
//            {"firstName", "John"},
//            {"lastName", "Doe"},
//            {"age", 30}
//        }},
//        {"contact", {
//            {"email", "john.doe@example.com"},
//            {"phone", "+1234567890"}
//        }},
//        {"metadata", {
//            {"createdAt", "2023-01-01"},
//            {"active", true}
//        }}
//    };
//
//    // 配置转换规则
//    JsonConverter converter;
//    converter
//        .add_rule(JsonConverter::rename_field(
//            "/personal/firstName", "/full_name"))
//        .add_rule(JsonConverter::transform_field(
//            "/personal/lastName", "/full_name",
//            [](const json& val) { return " " + val.get<std::string>(); }))
//        .add_rule(JsonConverter::rename_field(
//            "/personal/age", "/details/age"))
//        .add_rule(JsonConverter::rename_field(
//            "/contact/email", "/contact_info/email"))
//        .add_rule(JsonConverter::transform_field(
//            "/contact/phone", "/contact_info/phone",
//            [](const json& val) {
//                return val.get<std::string>().substr(0, 3) + "******";
//            }))
//        .add_rule(JsonConverter::constant_field(
//            "/system/version", "1.0.0"));
//
//            // 执行转换
//            json target = converter.convert(source);
//
//            // 输出结果
//            std::cout << "Converted JSON:\n" << target.dump(2) << std::endl;
//
//            // 写入文件
//            // std::ofstream("output.json") << target.dump(2);
//
//            return 0;
//}
