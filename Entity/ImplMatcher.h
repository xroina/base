/*--------1---------2---------3---------4---------5---------6---------7---*//**
 * @file
 *     モジュール名：共通メモリ管理機能マッチャインターフェース
 * <pre>
 *
 *    １  機能
 *          共通メモリ管理機能マッチャインターフェースを定義する
 *
 *    ２  更新履歴
 *          REV001 : 新規作成
 * </pre>
**//*-----1---------2---------3---------4---------5---------6---------7------*/

#ifndef _ENTITY_IMPLMATCHER_H
#define _ENTITY_IMPLMATCHER_H

#include <Entity/AppTable.h>

namespace Entity {

/*--------1---------2---------3---------4---------5---------6---------7---*//**
 *
 *     クラス名：共通メモリ管理機能マッチャインターフェース (CMatcherInterface)
 * <pre>
 *
 *    １    機能
 *          共通メモリ管理機能マッチャインターフェース
 *
 *    ２    履歴
 *            rev001 : 新規作成
 * </pre>
**//*-----1---------2---------3---------4---------5---------6---------7------*/
class ImplMatcher {
public:
    virtual ~ImplMatcher();

    // objが大きすぎたら正、小さすぎたら負、等しければ０を返す
    virtual int match(const AbstEntity&) const = 0;
};

class AbstIndexMatcher : public ImplMatcher {
private:
    const ::std::string& index_name;

public:
    AbstIndexMatcher(const ::std::string& name);
    virtual ~AbstIndexMatcher();

    virtual const ::std::string getIndexName() const;
};

class DefaultIndexMatcher : public AbstIndexMatcher {
public:
    DefaultIndexMatcher(const ::std::string& name);
    virtual ~DefaultIndexMatcher();

    // 必ずマッチ
    virtual int match(const AbstEntity& ent) const;
};

/*--------1---------2---------3---------4---------5---------6---------7---*//**
 *
 *     クラス名：共通メモリ管理機能コンペアラーインターフェース
 *               (CComparerInterface)
 * <pre>
 *
 *    １    機能
 *          共通メモリ管理機能コンペアラーインターフェース
 *          コンペアラーインターフェースは、インデクサインターフェイス
 *          (CIndexerInterface)とソータインターフェイス(CSorterInterface)の
 *          別名である。
 *
 * </pre>
**//*-----1---------2---------3---------4---------5---------6---------7------*/
class ImplSorter {
public:
    virtual ~ImplSorter();

    // obj1がobj2より大きければ正、小さければ負、等しければ０を返す
    virtual int compare(const AbstEntity&, const AbstEntity&) const = 0;
};

class ImplIndexer : public ImplSorter {
public:
    virtual ~ImplIndexer();

    virtual const ::std::string getIndexerName() const = 0;

};

/*--------1---------2---------3---------4---------5---------6---------7------*/
}   // end namespace Entity

#endif // _ENTITY_IMPLMATCHER_H
