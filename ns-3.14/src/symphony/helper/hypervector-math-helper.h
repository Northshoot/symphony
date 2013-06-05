/*
 * hypervector-math-helper.h
 *
 *  Created on: May 18, 2013
 *      Author: onir
 */

#ifndef HYPERVECTOR_MATH_HELPER_H_
#define HYPERVECTOR_MATH_HELPER_H_

namespace ns3 {

static class HypervectorMathHelper {

public:

	static void Xor(int *, int *, int*, int);
	static void Or(int *, int*, int*, int);
	static void Shift(int*, int int, int);
	static void double Sum (int*, int);

	static void Buff_int_to_bin(int*, int*, int);

};

} /* namespace ns3 */
#endif /* HYPERVECTOR_MATH_HELPER_H_ */
