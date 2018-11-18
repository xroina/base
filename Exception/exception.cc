/*--------1---------2---------3---------4---------5---------6---------7---*//**
 * CException.cpp
 *
 *  Created on: 2015/05/05
 *      Author: xronia
**//*-----1---------2---------3---------4---------5---------6---------7------*/

#include <Exception/exception.h>

namespace Exception {

/*--------1---------2---------3---------4---------5---------6---------7------*/

EXECPTION_FUNCTION_(domain_error,       ::std::domain_error,       算術想定範囲外の値が指定されました);
EXECPTION_FUNCTION_(invalid_argument,   ::std::invalid_argument,   不正な値が指定されました);
EXECPTION_FUNCTION_(length_error,       ::std::length_error,       処理可能な長さではありません);
EXECPTION_FUNCTION_(out_of_range,       ::std::out_of_range,       範囲外の値が指定されました);
EXECPTION_FUNCTION_(runtime_error,      ::std::runtime_error,      実行時エラーです);
EXECPTION_FUNCTION_(range_error,        ::std::range_error,        演算処理で値域外になりました);
EXECPTION_FUNCTION_(overflow,           ::std::overflow_error,     オーバーフローです);
EXECPTION_FUNCTION_(underflow,          ::std::underflow_error,    アンダーフローです);
/*--------1---------2---------3---------4---------5---------6---------7------*/
EXECPTION_FUNCTION_(nullpointer,        invalid_argument,   引数がnullでした);
EXECPTION_FUNCTION_(memoryfull,         length_error,       メモリがいっぱいです);
EXECPTION_FUNCTION_(size_mismatch,      length_error,       サイズが一致しません);
EXECPTION_FUNCTION_(not_define,         runtime_error,      定義されていない参照です);
EXECPTION_FUNCTION_(multi_define,       runtime_error,      複数定義されています);
EXECPTION_FUNCTION_(fileIO_error,       runtime_error,      ファイルIOエラーです);
EXECPTION_FUNCTION_(timeout,            runtime_error,      タイムアウトが発生しました);
EXECPTION_FUNCTION_(regex_error,        runtime_error,      正規表現による検索に失敗しました);
EXECPTION_FUNCTION_(lock_failed,        runtime_error,      ロックの取得に失敗しました);

/*--------1---------2---------3---------4---------5---------6---------7------*/

} /* end namespace Exception */
