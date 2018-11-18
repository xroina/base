/*--------1---------2---------3---------4---------5---------6---------7---*//**
 *
 * @file IIR_CB_AString.h
 *
 * @brief 配列型ストリング基底クラスのクラス定義を記述する。
 *
**//*-----1---------2---------3---------4---------5---------6---------7------*/
#ifndef STRING_ASTRING_H_
#define STRING_ASTRING_H_

#include <cstring>
#include <string>

namespace String {

/*--------1---------2---------3---------4---------5---------6---------7---*//**
 *
 * @class
 *    配列型ストリング基底クラス IIR_CB_AString
 *
 * @brief 文字列を扱うクラスである。
 *
 * @details
 *    文字列をオブジェクトとして扱うことを目的としている。<BR/>
 *    比較演算子を使って、二つの文字列が一致しているかどうかや、<BR/>
 *    大小関係を調べることができる。<BR/>
 *    代入演算子を使って文字列の代入ができる。<BR/>
 *    文字列のレングスを調べることができる。<BR/>
 *    ＋＝演算子を使って、文字列の連結ができる。
 *
**//*-----1---------2---------3---------4---------5---------6---------7------*/
template<int N> class astring {
protected:
    char _sText[N];                                 //  テキストデータ
public:
    astring();                                      // デフォルト構築子
    astring(const char*);                           // 構築子
    astring(const ::std::string&);                  // 構築子
    template<int M>
    astring(const astring<M>&);                     // コピー構築子
    ~astring();                                     // 消滅子
                                                    //    ※virtual指定は禁止（他プロセスからの
                                                    //      参照時にアドレス不正となるため）
    const char* c_str() const;                      // テキストデータ参照
    const ::std::string str() const;
    void set(const char*);                          // 設定関数
    template<int M>
    void set(const astring<M>&);
    void set(const ::std::string&);                 // 設定関数
    void clear();                                   // テキストデータ消去
    size_t length() const;                          // テキストレングス参照

    template<int M>
    bool operator==(const astring<M>&) const;       // ==演算子オーバロード
    bool operator==(const char*) const;
    bool operator==(const ::std::string&) const;

    template<int M>
    bool operator!=(const astring<M>&) const;       // !=演算子オーバロード
    bool operator!=(const char*) const;
    bool operator!=(const ::std::string&) const;

    template<int M>
    bool operator<(const astring<M>&) const;       // <演算子オーバロード
    bool operator<(const char*) const;
    bool operator<(const ::std::string&) const;

    template<int M>
    bool operator>(const astring<M>&) const;       // >演算子オーバロード
    bool operator>(const char*) const;
    bool operator>(const ::std::string&) const;

    template<int M>
    bool operator<=(const astring<M>&) const;       // <=演算子オーバロード
    bool operator<=(const char*) const;
    bool operator<=(const ::std::string&) const;

    template<int M>
    bool operator>=(const astring<M>&) const;       // >=演算子オーバロード
    bool operator>=(const char*) const;
    bool operator>=(const ::std::string&) const;

    template<int M>
    astring<N>& operator= (const astring<M>&);      // 代入演算子オーバロード
    astring<N>& operator= (const char*);
    astring<N>& operator= (const ::std::string&);

    template<int M>
    astring<N+M-1> operator+(const astring<M>&) const;
    astring<N> operator+(const char*) const;
    astring<N> operator+(const ::std::string&) const;

    template<int M>
    astring<N>& operator+=(const astring<M>&);
    astring<N>& operator+=(const char*);
    astring<N>& operator+=(const ::std::string&);

    operator ::std::string() const {
        return ::std::string(_sText);
    }

    explicit operator char*() const {
        return const_cast<char*>(_sText);
    }
};

/*--------1---------2---------3---------4---------5---------6---------7---*//**
 *
 * メンバ関数名
 *    デフォルト構築子
 *
 * @brief 配列型ストリングインスタンスのデフォルトの生成処理を行う。
 *
 * @details
 *    配列型ストリングインスタンスを生成する。
 *
 *     1 メンバーデータをクリアする。
 *
 * @param なし
 *
 * @return なし
 *
**//*-----1---------2---------3---------4---------5---------6---------7------*/
template<int N> astring<N>::astring() :_sText() {
    clear();
    return;
}

/*--------1---------2---------3---------4---------5---------6---------7---*//**
 *
 * メンバ関数名
 *    構築子
 *
 * @brief 配列型ストリングインスタンスの生成処理を行う。
 *
 * @details
 *    配列型ストリングインスタンスを生成し、引数値をテキストデータ(メンバ)に<BR/>
 *    設定して初期化する。
 *
 *     1 テキストデータを設定する。
 *
 * @param  sText ：      テキストデータ
 *
 * @return なし
 *
**//*-----1---------2---------3---------4---------5---------6---------7------*/
template<int N> astring<N>::astring(const char* sText) : _sText() {
    set(sText);
    return;
}

template<int N> astring<N>::astring(const ::std::string& sText) : _sText() {
    set(sText);
    return;
}

/*--------1---------2---------3---------4---------5---------6---------7---*//**
 *
 * メンバ関数名
 *    コピー構築子
 *
 * @brief 配列型ストリングインスタンスの生成処理を行う。
 *
 * @details
 *    配列型ストリングインスタンスを生成し、引数の配列型ストリングインスタンスの<BR/>
 *    持つテキストデータをメンバー変数に設定して初期化する。
 *
 *
 *     1 テキストデータを設定する。
 *
 * @param  roStr：       ストリング
 *
 * @return なし
 *
**//*-----1---------2---------3---------4---------5---------6---------7------*/
template<int N> template<int M>
inline astring<N>::astring(const astring<M>& sText) : _sText() {
    set(sText);
    return;
}

/*--------1---------2---------3---------4---------5---------6---------7---*//**
 *
 * メンバ関数名
 *    消滅子
 *
 * @brief 配列型ストリングインスタンスのクリア処理を行う。
 *
 * @details
 *    テキストデータ(メンバ)をクリアする。
 *
 *
 *     1 メンバーデータをクリアする。
 *
 * @param なし
 *
 * @return なし
 *
**//*-----1---------2---------3---------4---------5---------6---------7------*/
template<int N> astring<N>::~astring() {
    clear();
    return;
}

/*--------1---------2---------3---------4---------5---------6---------7---*//**
 *
 * メンバ関数名
 *    テキストデータ参照
 *
 * @brief テキストデータの取得処理を行う。
 *
 * @details
 *    配列型ストリングをconst char*型の戻り値に返す。
 *
 *
 *     1 終了処理を行う。
 *       テキストデータを戻る。
 *
 * @param なし
 *
 * @return  テキストデータ
 *
**//*-----1---------2---------3---------4---------5---------6---------7------*/
template<int N> const char* astring<N>::c_str() const {
    return const_cast<const char*>(_sText);
}

template<int N> const ::std::string astring<N>::str() const {
    return ::std::string(_sText);
}

/*--------1---------2---------3---------4---------5---------6---------7---*//**
 *
 * メンバ関数名
 *    テキストデータ設定
 *
 * @brief テキストデータを設定する。
 *
 * @details
 *    テキストデータ(メンバ)をクリアし、テキストデータ(引数値)がNULLでなく、<BR/>
 *    かつ、テキストデータ(引数値)のサイズが正の時、テキストデータを複製して、<BR/>
 *    テキストデータ(メンバ)に設定する。
 *
 *
 *     1 メンバーデータを事前クリアする。
 *     2 テキストデータを設定する。
 *     3 終了処理を行う。
 *
 * @param  sText ：      テキストデータ
 *
 * @return なし
 *
**//*-----1---------2---------3---------4---------5---------6---------7------*/
template<int N> void astring<N>::set(const char* sText) {
    clear();
    if(sText != nullptr  && ::strlen(sText) > 0) {
        if(::strlen(sText) + 1 <= N) {
            ::strcpy(_sText,  sText);
        } else {
            int nTrunc = ::strlen( sText ) + 1 - N;
            ::strncpy(_sText, sText + nTrunc, N - 1);
        }
    }
    return;
}
template<int N> template<int M>
void astring<N>::set(const astring<M>& sText) {
    set(sText.c_str());
}

template<int N> void astring<N>::set(const ::std::string& sText) {
    set(sText.c_str());
}
/*--------1---------2---------3---------4---------5---------6---------7---*//**
 *
 * メンバ関数名
 *    テキストデータ消去
 *
 * @brief テキストデータを消去する。
 *
 * @details
 *    テキストデータ(メンバ)をクリアする。
 *
 *
 *     1 メンバーデータをクリアする。
 *
 * @param なし
 *
 * @return なし
 *
**//*-----1---------2---------3---------4---------5---------6---------7------*/
template<int N> void astring<N>::clear() {
    ::memset(_sText, 0, sizeof(_sText));
    return;
}

/*--------1---------2---------3---------4---------5---------6---------7---*//**
 *
 * メンバ関数名
 *    テキストレングス参照
 *
 * @brief テキストデータ文字列長の取得処理を行う。
 *
 * @details
 *    配列型ストリングを文字列長の戻り値に返す。
 *
 *
 *     1 終了処理を行う。
 *       テキストデータレングスを返す。
 *
 * @param なし
 *
 * @return 文字列長
 *
**//*-----1---------2---------3---------4---------5---------6---------7------*/
template<int N> size_t astring<N>::length() const {
    return ::strlen(_sText);
}

/*--------1---------2---------3---------4---------5---------6---------7---*//**
 *
 * メンバ関数名
 *    ＝＝演算子オーバロード
 *
 * @brief ＝＝演算子を定義する。
 *
 * @details
 *    自身のストリングと引数値のストリング（IIR_CB_AString型）を比較して、<BR/>
 *    一致ならtrue、不一致ならfalseを返す。
 *
 *
 *     1 自身のテキストデータと引数値のテキストデータを比較して、
 *       一致ならtrue、不一致ならfalseを返す。
 *
 *
 * @param   roStr ：      ストリング
 *
 *  @return  true  ： 自身のストリングと引数値のストリングが一致
 *  @return  false ： 自身のストリングと引数値のストリングが不一致
 *
**//*-----1---------2---------3---------4---------5---------6---------7------*/
template<int N> template<int M>
 bool astring<N>::operator==(const astring<M>& roStr) const {
    return ::strcmp(_sText, roStr.c_str()) == 0;
}

/*--------1---------2---------3---------4---------5---------6---------7---*//**
 *
 * メンバ関数名
 *    ＝＝演算子オーバロード
 *
 * @brief ＝＝演算子を定義する。
 *
 * @details
 *    自身のストリングと引数値の文字列（const char*型）を比較して、<BR/>
 *    一致ならtrue、不一致ならfalseを返す。
 *
 *
 *     1 バッファを\0にセットする。
 *     2 引数文字列がNULLの場合
 *         2.1 バッファを引数文字列にセットする。
 *     3 自身のテキストデータと引数値の文字列を比較して、
 *       一致ならtrue、不一致ならfalseを返す。
 *
 * @param     sStr ：       文字列
 *
 *  @return  true  ： 自身のストリングと引数値の文字列が一致
 *  @return  false ： 自身のストリングと引数値の文字列が不一致
 *
**//*-----1---------2---------3---------4---------5---------6---------7------*/
template<int N> bool astring<N>::operator==(const char* sStr) const {
    const char* sWrkStr = sStr;
    static char sBuf[2] = "\0";
    if(sStr == nullptr) sWrkStr = sBuf;
    return ::strcmp(c_str(), sWrkStr) == 0 ? true : false;
}

template<int N> bool astring<N>::operator==(const ::std::string& sStr) const {
    return ::strcmp(_sText, sStr.c_str()) == 0;
}

/*--------1---------2---------3---------4---------5---------6---------7---*//**
 *
 * メンバ関数名
 *    ！＝演算子オーバロード
 *
 * @brief ！＝演算子を定義する。
 *
 * @details
 *    自身のストリングと引数値のストリング（IIR_CB_AString型）を比較して、<BR/>
 *    不一致ならtrue、一致ならfalseを返す。
 *
 *
 *     1 自身のテキストデータと引数値のテキストデータを比較して、
 *       不一致ならtrue、一致ならfalseを返す。
 *
 * @param    roStr ：     ストリング
 *
 *  @return  true  ： 自身のストリングと引数値のストリングが不一致
 *  @return  false ： 自身のストリングと引数値のストリングが一致
 *
**//*-----1---------2---------3---------4---------5---------6---------7------*/
template<int N> template<int M>
inline bool astring<N>::operator!=(const astring<M>&roStr) const {
    return ::strcmp(_sText, roStr.c_str()) != 0;
}

/*--------1---------2---------3---------4---------5---------6---------7---*//**
 *
 * メンバ関数名
 *    ！＝演算子オーバロード
 *
 * @brief ！＝演算子を定義する。
 *
 * @details
 *    自身のストリングと引数値の文字列（const char*型）を比較して、<BR/>
 *    不一致ならtrue、一致ならfalseを返す。
 *
 *
 *     1 バッファを\0にセットする。
 *     2 文字列がNULLの場合。
 *         2.1 バッファを文字列にセットする。
 *     3 自身のテキストデータと引数値の文字列を比較して、
 *       不一致ならtrue、一致ならfalseを返す。
 *
 * @param    sStr  ：       文字列
 *
 *  @return  true  ：  自身のストリングと引数値の文字列が不一致
 *  @return  false ：  自身のストリングと引数値の文字列が一致
 *
**//*-----1---------2---------3---------4---------5---------6---------7------*/
template<int N> bool astring<N>::operator!=(const char* sStr) const  {
    const char* sWrkStr = sStr;
    static char sBuf[2] = "\0";
    if(sStr == nullptr) sWrkStr = sBuf;
    return ::strcmp(_sText, sWrkStr) != 0;
}

template<int N> bool astring<N>::operator!=(const ::std::string& sStr) const {
    return ::strcmp(_sText, sStr.c_str()) != 0;
}

/*--------1---------2---------3---------4---------5---------6---------7---*//**
 *
 * メンバ関数名
 *    ＜演算子オーバロード
 *
 * @brief ＜演算子を定義する。
 *
 * @details
 *    自身のストリングと引数値のストリング（IIR_CB_AString型）を比較して、<BR/>
 *    引数値のストリングの方が小さければtrue、そうでなければfalseを返す。
 *
 *
 *     1 自身のテキストデータ＜引数値のテキストデータならtrue、そうでなければfalseを返す。
 *
 * @param     roStr ：    ストリング
 *
 *  @return   true  ： 自身のストリングより引数値のストリングの方が小さい
 *  @return   false ： 上記以外
 *
 * 備考
 *    なし
 *
**//*-----1---------2---------3---------4---------5---------6---------7------*/
template<int N> template<int M>
bool astring<N>::operator<(const astring<M>& roStr) const {
    return ::strcmp(_sText, roStr.c_str()) < 0;
}

template<int N>
bool astring<N>::operator<(const char* sStr) const {
    const char* sWrkStr = sStr;
    static char sBuf[2] = "\0";
    if(sStr == nullptr) sWrkStr = sBuf;
    return ::strcmp(_sText, sWrkStr) < 0;
}

template<int N>
bool astring<N>::operator<(const ::std::string& roStr) const {
    return ::strcmp(_sText, roStr.c_str()) < 0;
}

/*--------1---------2---------3---------4---------5---------6---------7---*//**
 *
 * メンバ関数名
 *    ＞演算子オーバロード
 *
 * @brief ＞演算子を定義する。
 *
 * @details
 *    自身のストリングと引数値のストリング（IIR_CB_AString型）を比較して、<BR/>
 *    自身のストリングの方が大きければtrue、そうでなければfalseを返す。
 *
 *
 *     1 自身のテキストデータ＞引数値のテキストデータならtrue、そうでなければfalseを返す。
 *
 * @param   roStr ：      ストリング
 *
 *  @return  true  ： 自身のストリングの方が引数値のストリングより大きい
 *  @return  false ： 上記以外
 *
**//*-----1---------2---------3---------4---------5---------6---------7------*/
template<int N> template<int M>
bool astring<N>::operator>(const astring<M>& roStr ) const {
    return ::strcmp(_sText, roStr.c_str()) > 0;
}

template<int N>
bool astring<N>::operator>(const char* sStr) const {
    const char* sWrkStr = sStr;
    static char sBuf[2] = "\0";
    if(sStr == nullptr) sWrkStr = sBuf;
    return ::strcmp(_sText, sWrkStr) > 0;
}

template<int N>
bool astring<N>::operator>(const ::std::string& roStr) const {
    return ::strcmp(_sText, roStr.c_str()) > 0;
}

/*--------1---------2---------3---------4---------5---------6---------7---*//**
 *
 * メンバ関数名
 *    ＜＝演算子オーバロード
 *
 * @brief ＜＝演算子を定義する。
 *
 * @details
 *    自身のストリングと引数値のストリング（IIR_CB_AString型）を比較して、<BR/>
 *    引数値のストリングが自身のストリングと同じか大きければtrue、<BR/>
 *    そうでなければfalseを返す。
 *
 *
 *     1 自身のテキストデータ＜＝引数値のテキストデータならtrue、そうでなければfalseを返す。
 *
 * @param  roStr  ：     ストリング
 *
 *  @return  true  ： 引数値のストリングが自身のストリングと同じか大きい
 *  @return  false ： 上記以外
 *
**//*-----1---------2---------3---------4---------5---------6---------7------*/
template<int N> template<int M>
bool astring<N>::operator<=(const astring<M>& roStr) const {
    return ::strcmp(_sText, roStr.c_str()) <= 0;
}

template<int N>
bool astring<N>::operator<=(const char* sStr) const {
    const char* sWrkStr = sStr;
    static char sBuf[2] = "\0";
    if(sStr == nullptr) sWrkStr = sBuf;
    return ::strcmp(_sText, sWrkStr) <= 0;
}

template<int N>
bool astring<N>::operator<=(const ::std::string& roStr) const {
    return ::strcmp(_sText, roStr.c_str()) <= 0;
}

/*--------1---------2---------3---------4---------5---------6---------7---*//**
 *
 * メンバ関数名
 *    ＞＝演算子オーバロード
 *
 * @brief ＞＝演算子を定義する。
 *
 * @details
 *    自身のストリングと引数値のストリング（IIR_CB_AString型）を比較して、<BR/>
 *    自身のストリングが引数値のストリングと同じか大きければtrue、<BR/>
 *    そうでなければfalseを返す。
 *
 *
 *     1 自身のテキストデータ＞＝引数値のテキストデータならtrue、そうでなければfalseを返す。
 *
 * @param    roStr ：   ストリング
 *
 *  @return  true  ： 自身のストリングが引数値のストリングと同じか大きい
 *  @return  false ： 上記以外
 *
**//*-----1---------2---------3---------4---------5---------6---------7------*/
template<int N> template<int M>
bool astring<N>::operator>=(const astring<M>& roStr) const {
    return ::strcmp(_sText, roStr.c_str()) >= 0;
}

template<int N>
bool astring<N>::operator>=(const char* sStr) const {
    const char* sWrkStr = sStr;
    static char sBuf[2] = "\0";
    if(sStr == nullptr) sWrkStr = sBuf;
    return ::strcmp(_sText, sWrkStr) >= 0;
}

template<int N>
bool astring<N>::operator>=(const ::std::string& roStr) const {
    return ::strcmp(_sText, roStr.c_str()) >= 0;
}

/*--------1---------2---------3---------4---------5---------6---------7---*//**
 *
 * メンバ関数名
 *    ＝代入演算子オーバロード
 *
 * @brief ＝代入演算子を定義する。
 *
 * @details
 *    引数のストリング（IIR_CB_AString型）の文字列を自身のストリングに設定し、<BR/>
 *    IIR_CB_AStringクラスインスタンスのポインタを返す。
 *
 *
 *     1 引数値のテキストデータをセットする。
 *     2 オブジェクトへのポインタを返す。
 *
 * @param   roStr ：      ストリング
 *
 * @return IIR_CB_AStringクラスインスタンスのポインタ
 *
**//*-----1---------2---------3---------4---------5---------6---------7------*/
template<int N> template<int M>
astring<N>& astring<N>::operator=(const astring<M>& roStr) {
    set(roStr);
    return *this;
}

/*--------1---------2---------3---------4---------5---------6---------7---*//**
 *
 * メンバ関数名
 *    ＝代入演算子オーバロード
 *
 * @brief ＝代入演算子を定義する。
 *
 * @details
 *    引数の文字列（const char*型）を自身のストリングに設定し、<BR/>
 *    IIR_CB_AStringクラスインスタンスのポインタを返す。
 *
 *
 *     1 引数値の文字列をセットする。
 *     2 文字列へのポインタを返す。
 *
 * @param    sStr ：       文字列
 *
 * @return  IIR_CB_AStringクラスインスタンスのポインタ
 *
**//*-----1---------2---------3---------4---------5---------6---------7------*/
template<int N> astring<N>& astring<N>::operator=(const char* sStr) {
    set(sStr);
    return *this;
}

template<int N> astring<N>& astring<N>::operator=(const ::std::string& sStr) {
    set(sStr);
    return *this;
}

template<int N> template<int M>
astring<N+M-1> astring<N>::operator+(const astring<M>& roStr) const {
    astring<N+M-1> ret(this->str() + roStr.str());
    return ret;
}

template<int N>
astring<N> astring<N>::operator+(const char* sStr) const {
    const char* sWrkStr = sStr;
    static char sBuf[2] = "\0";
    if(sStr == nullptr) sWrkStr = sBuf;
    astring<N> ret(this->str() + sWrkStr);
    return ret;
}

template<int N>
astring<N> astring<N>::operator+(const ::std::string& in) const {
    astring<N> ret(this->str() + in);
    return ret;
}

/*--------1---------2---------3---------4---------5---------6---------7---*//**
 *
 * メンバ関数名
 *    ＋＝代入演算子オーバロード
 *
 * @brief ＋＝代入演算子を定義する。
 *
 * @details
 *    引数のストリング（IIR_CB_AString型）の文字列を自身のストリングに連結し、<BR/>
 *    IIR_CB_AStringクラスインスタンスのポインタを返す。
 *
 *
 *     1 自身のテキストデータと引数で渡されたテキストデータの長さを足す。
 *     2 変数バッファを定義する。
 *     3 バッファの領域を確保する。
 *     4 自身のテキストデータと引数で渡されたテキストデータを連結する。
 *     5 バッファをセットする。
 *     6 バッファの領域を解放する。
 *     7 オブジェクトへのポインタを返す。
 *
 * @param   roStr ：      ストリング
 *
 * @return  IIR_CB_AStringクラスインスタンスのポインタ
 *
**//*-----1---------2---------3---------4---------5---------6---------7------*/
template<int N> template<int M>
astring<N>& astring<N>::operator+=(const astring<M>& roStr) {
    set(this->str() + roStr.str());
    return *this;
}

template<int N>
astring<N>& astring<N>::operator+=(const char* in) {
    const char* sWrkStr = in;
    static char sBuf[2] = "\0";
    if(in == nullptr) sWrkStr = sBuf;
    set(this->str() + sWrkStr);
    return *this;
}

template<int N>
astring<N>& astring<N>::operator+=(const ::std::string& in) {
    set(this->str() + in);
    return *this;
}

template<int N>
::std::ostream& operator<<(::std::ostream& out, const astring<N>& in) {
    out << in.c_str();
    return out;
}

/*--------1---------2---------3---------4---------5---------6---------7------*/
}   // end namespace String

#endif  /* STRING_ASTRING_H_ */
