/*--------1---------2---------3---------4---------5---------6---------7---*//**
 * Tuple.h
 *
 *  Created on: 2018/08/04
 *      Author: xronia
**//*-----1---------2---------3---------4---------5---------6---------7------*/

#ifndef ENTITY_INDEXNAME_H_
#define ENTITY_INDEXNAME_H_

#include <Entity/AppTable.h>
#include <String/astring.h>
#include <Entity/ImplMatcher.h>

namespace Entity {

class IndexName : public AbstEntity {
public:
    static constexpr char ENTITY_NAME[] = "$INDEX";

    entityname_t entity_name;   ///< エンティティ名
    entityname_t index_id;      ///< インデックスID
    entityname_t index_name;    ///< インデックス名
    entityname_t indexer_name;  ///< インデクサ名
    rowid_t index_root;         ///< インデックスのrowid

    IndexName();
    IndexName(const entityname_t&, const entityname_t&,
            const entityname_t&, const entityname_t&, const rowid_t&);
    ~IndexName();

    /// タプルに値をコピー
    void set(const entityname_t&, const entityname_t&,
            const entityname_t&, const entityname_t&, const rowid_t&);
};

/*--------1---------2---------3---------4---------5---------6---------7---*//**
* クラス名 : ノードインデクサ (CNodeIndexer)
**//*-----1---------2---------3---------4---------5---------6---------7------*/
class IndexNameIndexer : public ImplIndexer {
public:
    static constexpr char INDEXER_NAME[]  = "$INDEX$INDEX";

    IndexNameIndexer();
    virtual ~IndexNameIndexer();
    /// 比較処理
    int compare(const AbstEntity&, const AbstEntity&) const;

    const ::std::string getIndexerName() const;
};

/*--------1---------2---------3---------4---------5---------6---------7---*//**
* クラス名 : ノードマッチャ (CNodeMatcher)
**//*-----1---------2---------3---------4---------5---------6---------7------*/
class IndexNameMatcher : public AbstIndexMatcher {
private:
    const entityname_t entity_name;        ///< エンティティ名
    const entityname_t index_id;           ///< インデックスID
public:
    /// コンストラクタ
    explicit IndexNameMatcher(const entityname_t, const entityname_t);
    virtual ~IndexNameMatcher();
    /// マッチ処理
    int match(const AbstEntity&) const;
};

/*--------1---------2---------3---------4---------5---------6---------7------*/

} /* end namespace Entity */

#endif /* ENTITY_INDEXNAME_H_ */
