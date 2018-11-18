/*--------1---------2---------3---------4---------5---------6---------7---*//**
 * @file
 *     モジュール名：テーブル情報定義構造体ヘッダ
 * <pre>
 *
 *    １  機能
 *        テーブル情報定義構造体を定義する
 *
 *    ２  更新履歴
 *          REV001 : 新規作成
 * </pre>
**//*-----1---------2---------3---------4---------5---------6---------7------*/
#ifndef ENTITY_ENTITYDEF_H_
#define ENTITY_ENTITYDEF_H_

#include <string>
#include <map>

namespace Entity {

/// 列情報構造体
class Column {
public:
    enum Type {
        NONE,
        BOOL,                                   ///< bool型
        INT8,                                   ///< int8_t整数型
        INT16,                                  ///< int16_t整数型
        INT32,                                  ///< int32_t整数型
        INT64,                                  ///< int64_t整数型
        UINT8,                                  ///< 符号無しint8_t整数型
        UINT16,                                 ///< 符号無しint16_t整数型
        UINT32,                                 ///< 符号無しint32_t整数型
        UINT64,                                 ///< 符号無しint64_t整数型
        FLOAT,                                  ///< 単精度実数型
        DOUBLE,                                 ///< 倍精度実数型
        CHAR_ARRAY,                             ///< char配列型
        TIME,                                   ///< 日時型
        MTIME,                                  ///< 日時型(ms)
        NTIME,                                  ///< 日時＋nSec型
        ASTRING,                                ///< astring型
        ENUM,                                   ///< APP定義列挙子型
        STRUCT,                                 ///< APP定義構造体型
        RECKEY,                                 ///< レコードキー型
        ANYDATA,                                ///< 可変長型
        ENTITY,                                 ///< APP定義クラスポインタ型
    };

    const Type type;                            ///< 型定義
    const int key;                              ///< 1以上:キー/0:非キー
    const size_t offset;                        ///< メンバオフセット
    const size_t size;                          ///< メンバサイズ

    Column(const Type, const int, const size_t, const size_t);
    ~Column();
};

/// テーブル情報構造体
class EntityDef {
private:
    typedef ::std::map<::std::string, Column> Columns;
public:
    const size_t size;                          ///< テーブルサイズ
    const Columns columns;                      ///< 列情報定義構造体配列

    EntityDef(const size_t, const Columns);
    ~EntityDef();
};


/*--------1---------2---------3---------4---------5---------6---------7------*/
} // end namespace Entity

#define OFFSET(type, member)                                                \
    (reinterpret_cast<::std::size_t>(                                       \
        &reinterpret_cast<char const volatile&>(                            \
                ((type*)0)->member)))

#endif /* ENTITY_ENTITYDEF_H_ */
