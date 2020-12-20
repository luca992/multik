package org.jetbrains.kotlinx.multik.api

import org.jetbrains.kotlinx.multik.ndarray.data.*

/**
 * Statistics methods interface.
 */
public interface Statistics {

    /**
     * Returns the median of the [a] elements.
     */
    public fun <T : Number, D : Dimension> median(a: MultiArray<T, D>): Double?

    /**
     * Returns the weighted average over the [a] elements and [weights] elements.
     */
    public fun <T : Number, D : Dimension> average(a: MultiArray<T, D>, weights: MultiArray<T, D>? = null): Double

    /**
     * Returns the arithmetic mean of the [a] elements.
     */
    public fun <T : Number, D : Dimension> mean(a: MultiArray<T, D>): Double

    /**
     * Returns the arithmetic mean of the [a] elements along the given [axis].
     */
    public fun <T : Number, D : Dimension, O : Dimension> mean(a: MultiArray<T, D>, axis: Int): Ndarray<Double, O>

    /**
     * Returns the arithmetic mean of the two-dimensional ndarray [a] elements along the given [axis].
     */
    public fun <T : Number> meanD2(a: MultiArray<T, D2>, axis: Int): Ndarray<Double, D1>

    /**
     * Returns the arithmetic mean of the three-dimensional ndarray [a] elements along the given [axis].
     */
    public fun <T : Number> meanD3(a: MultiArray<T, D3>, axis: Int): Ndarray<Double, D2>

    /**
     * Returns the arithmetic mean of the four-dimensional ndarray [a] elements along the given [axis].
     */
    public fun <T : Number> meanD4(a: MultiArray<T, D4>, axis: Int): Ndarray<Double, D3>

    /**
     * Returns the arithmetic mean of the n-dimensional ndarray [a] elements along the given [axis].
     */
    public fun <T : Number> meanDN(a: MultiArray<T, DN>, axis: Int): Ndarray<Double, D4>
}

/**
 * Returns the absolute value of the given ndarray [a].
 */
@JvmName("absByte")
public fun <D : Dimension> Statistics.abs(a: MultiArray<Byte, D>): Ndarray<Byte, D> {
    val ret = initMemoryView<Byte>(a.size, a.dtype)
    var index = 0
    for (element in a) {
        ret[index++] = absByte(element)
    }
    return Ndarray(ret, 0, a.shape.copyOf(), dtype = a.dtype, dim = a.dim)
}

@JvmName("absShort")
public fun <D : Dimension> Statistics.abs(a: MultiArray<Short, D>): Ndarray<Short, D> {
    val ret = initMemoryView<Short>(a.size, a.dtype)
    var index = 0
    for (element in a) {
        ret[index++] = absShort(element)
    }
    return Ndarray(ret, 0, a.shape.copyOf(), dtype = a.dtype, dim = a.dim)
}

@JvmName("absInt")
public fun <D : Dimension> Statistics.abs(a: MultiArray<Int, D>): Ndarray<Int, D> {
    val ret = initMemoryView<Int>(a.size, a.dtype)
    var index = 0
    for (element in a) {
        ret[index++] = kotlin.math.abs(element)
    }
    return Ndarray(ret, 0, a.shape.copyOf(), dtype = a.dtype, dim = a.dim)
}

@JvmName("absLong")
public fun <D : Dimension> Statistics.abs(a: MultiArray<Long, D>): Ndarray<Long, D> {
    val ret = initMemoryView<Long>(a.size, a.dtype)
    var index = 0
    for (element in a) {
        ret[index++] = kotlin.math.abs(element)
    }
    return Ndarray(ret, 0, a.shape.copyOf(), dtype = a.dtype, dim = a.dim)
}

@JvmName("absFloat")
public fun <D : Dimension> Statistics.abs(a: MultiArray<Float, D>): Ndarray<Float, D> {
    val ret = initMemoryView<Float>(a.size, a.dtype)
    var index = 0
    for (element in a) {
        ret[index++] = kotlin.math.abs(element)
    }
    return Ndarray(ret, 0, a.shape.copyOf(), dtype = a.dtype, dim = a.dim)
}

@JvmName("absDouble")
public fun <D : Dimension> Statistics.abs(a: MultiArray<Double, D>): Ndarray<Double, D> {
    val ret = initMemoryView<Double>(a.size, a.dtype)
    var index = 0
    for (element in a) {
        ret[index++] = kotlin.math.abs(element)
    }
    return Ndarray(ret, 0, a.shape.copyOf(), dtype = a.dtype, dim = a.dim)
}

private inline fun absByte(a: Byte): Byte = if (a < 0) (-a).toByte() else a

private inline fun absShort(a: Short): Short = if (a < 0) (-a).toShort() else a