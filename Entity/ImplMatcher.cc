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

#include <Entity/ImplMatcher.h>

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
ImplMatcher::~ImplMatcher() {
}

AbstIndexMatcher::AbstIndexMatcher(const ::std::string& name) :
        index_name(name) {
}

AbstIndexMatcher::~AbstIndexMatcher() {
}

const ::std::string AbstIndexMatcher::getIndexName() const {
    return index_name;
}

DefaultIndexMatcher::DefaultIndexMatcher(const ::std::string& name) :
        AbstIndexMatcher(name) {
}

DefaultIndexMatcher::~DefaultIndexMatcher() {
}

// 必ずマッチ
int DefaultIndexMatcher::match(const AbstEntity& ent) const {
    return 0;
}

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
ImplSorter::~ImplSorter() {
}

ImplIndexer::~ImplIndexer() {
}

/*--------1---------2---------3---------4---------5---------6---------7------*/
}   // end namespace Entity
