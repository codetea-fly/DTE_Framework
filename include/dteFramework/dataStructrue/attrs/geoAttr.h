#pragma once
#include "attribute.h"
class DTEFramework_API geoAttr :
    public attribute
{
public:
    int length = 0;
    std::string geoUri;
    class mesh {
    public:
        std::string id;
        std::string name;
        class boxData {
        public:
            std::array<double, 6> boxes;
            int gid;
            int mid;
            int modelType;
            std::array<double, 16> transform;
            boxData(std::array<double, 6> o1, int o2, int o3, int o4, std::array<double, 16> o5) :gid(o2), mid(o3), modelType(o4) {
                std::copy(std::begin(o1), std::end(o1), std::begin(boxes));
                std::copy(std::begin(o5), std::end(o5), std::begin(transform));
            }
        };
        std::vector<boxData> boxes;
        mesh(std::string o1, std::string o2, std::vector<boxData> o3) : id(o1),name(o2),boxes(o3) {}
    };
    class dataView {
    public:
        int byteOffset;
        int byteLength;
        int pos_itemSize = 3;
        int pos_rangeL = 0;
        int pos_rangeR = 0;
        int nor_itemSize = 3;
        int nor_rangeL = 0;
        int nor_rangeR = 0;
        int uv_itemSize = 2;
        int uv_rangeL = 0;
        int uv_rangeR = 0;
        int face_itemSize = 1;
        int face_rangeL = 0;
        int face_rangeR = 0;
        dataView(int o1, int o2, int o3, int o4, int o5, int o6, int o7, int o8, int o9, int o10, int o11, int o12, int o13, int o14) :
            byteOffset(o1),byteLength(o2),pos_itemSize(o3),pos_rangeL(o4),pos_rangeR(o5),nor_itemSize(o6),
            nor_rangeL(o7),nor_rangeR(o8),uv_itemSize(o9), uv_rangeL(o10), uv_rangeR(o11), face_itemSize(o12),
            face_rangeL(o13),face_rangeR(o14){}
        //TO-DO to_json
    };
    class meterial {
    public:
        int color;
        std::string name;
        double roughness;
        double opacity;
        bool transparent;
        double metalness;
        int texture_map_index = -1;
        double texture_map_scale_first = -1;
        double texture_map_scale_second = -1;
        int texture_bump_index = -1;
        double texture_bump_scale_first = -1;
        double texture_bump_scale_second = -1;
        meterial(int o1, std::string o2, double o3, double o4, bool o5, double o6, int o7, double o8, double o9, int o10, double o11, double o12) :
            color(o1), name(o2), roughness(o3), opacity(o4), transparent(o5), metalness(o6), texture_map_index(o7), texture_map_scale_first(o8),
            texture_map_scale_second(o9), texture_bump_index(o10), texture_bump_scale_first(o11), texture_bump_scale_second(o12)
        {}
    };
    std::vector<int> transform;
    std::vector<dataView> dataViews;
    std::vector<meterial> meterials;
    std::vector<std::string> textures;
    std::vector<mesh> meshes;
    geoAttr() {};
    geoAttr(int o1, std::string o2, std::vector<int> o3, std::vector<dataView> o4, std::vector<meterial> o5, std::vector<std::string> o6, std::vector<mesh> o7):
    length(o1), geoUri(o2), transform(o3), dataViews(o4), meterials(o5), textures(o6), meshes(o7)
    {};
//public:
//    int byteOffset = 0;
//    int byteLength = 0;
//    class dataView {
//        std::string name;
//        std::string type;
//        int itemSize;
//        int range_L;
//        int range_R;
//    public:
//        dataView(std::string n, std::string t, int i, int range_left, int range_right) {
//            name = n;
//            type = t;
//            itemSize = i;
//            range_L = range_left;
//            range_R = range_right;
//        }
//
//        std::string print() {
//            std::string result;
//            if (!name.empty()) {
//                result += "name:";
//                result += name;
//                result += "\ntype:";
//                result += type;
//                result += "\nitemSize:";
//                result += itemSize;
//                result += "\nrange_L:";
//                result += range_L;
//                result += "\nrange_R:";
//                result += range_R;
//            }
//            return result;
//        }
//    };
//    std::vector<dataView> byteDataArray;
//
//    void initFromGML(int offset,  int length) {
//        byteOffset = offset;
//        byteLength = length;
//    }
//
//    void addDataView(dataView d) {
//        byteDataArray.emplace_back(d);
//    }
//
//    std::string print() override {
//        std::string result = attribute::print();
//        //TO-DO 几何格式定义
//        for (dataView d : byteDataArray) {
//            result += d.print();
//            result += "\n";
//        }
//        return result;
//    }
};

