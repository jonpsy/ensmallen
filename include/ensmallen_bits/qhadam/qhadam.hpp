/**
 * @file adamw.hpp
 * @author Niteya Shah
 *
 */
#ifndef ENSMALLEN_ADAM_ADAMW_HPP
#define ENSMALLEN_ADAM_ADAMW_HPP

 #include <ensmallen_bits/sgd/sgd.hpp>
#include "qhadam_update.hpp"

 namespace ens {

 /**
 * QHadam is an variation of Adam with Quasi-Hyperbolic step. It can be
 * a weighted mean of the momentum step. Due to its paramterisation it can
 * recover many other optimisation strategies.
 *
 * For more information, see the following.
 *
 * @code
 * @inproceedings{ma2019qh,
 *   title={Quasi-hyperbolic momentum and Adam for deep learning},
 *   author={Jerry Ma and Denis Yarats},
 *   booktitle={International Conference on Learning Representations},
 *   year={2019}
 * }
 * @endcode
 *
 * QHAdam can optimize differentiable separable functions.
 * For more details, see the documentation on function
 * types included with this distribution or on the ensmallen website.
 */
class QHAdam
{
 public:
  /**
   * Construct the QHAdam optimizer with the given function and parameters.
   * QHAdam is sensitive to its paramters and hence a good hyper paramater
   * selection is necessary as its default may not fit every case.
   *
   * The maximum number of iterations refers to the maximum number of
   * points that are processed (i.e., one iteration equals one point; one
   * iteration does not equal one pass over the dataset).
   *
   * @param stepSize Step size for each iteration.
   * @param batchSize Number of points to process in a single step.
   * @param v1 The first quasi-hyperbolic term.
   * @param v1 The second quasi-hyperbolic term.
   * @param beta1 Exponential decay rate for the first moment estimates.
   * @param beta2 Exponential decay rate for the weighted infinity norm
            estimates.
   * @param eps Value used to initialise the mean squared gradient parameter.
   * @param maxIterations Maximum number of iterations allowed (0 means no
   *        limit).
   * @param tolerance Maximum absolute tolerance to terminate algorithm.
   * @param shuffle If true, the function order is shuffled; otherwise, each
   *        function is visited in linear order.
   * @param resetPolicy If true, parameters are reset before every Optimize
   *        call; otherwise, their values are retained.
   */

   QHAdam(const double stepSize = 0.001,
          const size_t batchSize = 32,
          const double v1 = 0.7,
          const double v2 = 1,
          const double beta1 = 0.9,
          const double beta2 = 0.999,
          const double epsilon = 1e-8,
          const size_t maxIterations = 100000,
          const double tolerance = 1e-5,
          const bool shuffle = true,
          const bool resetPolicy = true);

   /**
   * Optimize the given function using QHAdam. The given starting point will be
   * modified to store the finishing point of the algorithm, and the final
   * objective value is returned.
   *
   * @tparam DecomposableFunctionType Type of the function to optimize.
   * @param function Function to optimize.
   * @param iterate Starting point (will be modified).
   * @return Objective value of the final point.
   */
  template<typename DecomposableFunctionType>
  double Optimize(DecomposableFunctionType& function, arma::mat& iterate)
  {
    return optimizer.Optimize(function, iterate);
  }

   //! Get the step size.
  double StepSize() const { return optimizer.StepSize(); }
  //! Modify the step size.
  double& StepSize() { return optimizer.StepSize(); }

   //! Get the batch size.
  size_t BatchSize() const { return optimizer.BatchSize(); }
  //! Modify the batch size.
  size_t& BatchSize() { return optimizer.BatchSize(); }

   //! Get the smoothing parameter.
  double Beta1() const { return optimizer.UpdatePolicy().Beta1(); }
  //! Modify the smoothing parameter.
  double& Beta1() { return optimizer.UpdatePolicy().Beta1(); }

   //! Get the second moment coefficient.
  double Beta2() const { return optimizer.UpdatePolicy().Beta2(); }
  //! Modify the second moment coefficient.
  double& Beta2() { return optimizer.UpdatePolicy().Beta2(); }

   //! Get the value used to initialise the mean squared gradient parameter.
  double Epsilon() const { return optimizer.UpdatePolicy().Epsilon(); }
  //! Modify the value used to initialise the mean squared gradient parameter.
  double& Epsilon() { return optimizer.UpdatePolicy().Epsilon(); }

   //! Get the maximum number of iterations (0 indicates no limit).
  size_t MaxIterations() const { return optimizer.MaxIterations(); }
  //! Modify the maximum number of iterations (0 indicates no limit).
  size_t& MaxIterations() { return optimizer.MaxIterations(); }

   //! Get the tolerance for termination.
  double Tolerance() const { return optimizer.Tolerance(); }
  //! Modify the tolerance for termination.
  double& Tolerance() { return optimizer.Tolerance(); }

   //! Get whether or not the individual functions are shuffled.
  bool Shuffle() const { return optimizer.Shuffle(); }
  //! Modify whether or not the individual functions are shuffled.
  bool& Shuffle() { return optimizer.Shuffle(); }

   //! Get whether or not the update policy parameters
  //! are reset before Optimize call.
  bool ResetPolicy() const { return optimizer.ResetPolicy(); }
  //! Modify whether or not the update policy parameters
  //! are reset before Optimize call.
  bool& ResetPolicy() { return optimizer.ResetPolicy(); }

   //! Get the first quasi hyperbolic parameter.
  double V1() const { return optimizer.UpdatePolicy().V1(); }
  //! Modify the first quasi hyperbolic parameter.
  double& V1() { return optimizer.UpdatePolicy().V1(); }

  //! Get the second quasi hyperbolic parameter.
  double V2() const { return optimizer.UpdatePolicy().V2(); }
  //! Modify the second quasi hyperbolic parameter.
  double& V2() { return optimizer.UpdatePolicy().V2(); }

  private:
  //! The Stochastic Gradient Descent object with AdamW policy.
  SGD<QHAdamUpdate> optimizer;
};

} // namespace ens

 // Include implementation.
#include "qhadam_impl.hpp"

 #endif
