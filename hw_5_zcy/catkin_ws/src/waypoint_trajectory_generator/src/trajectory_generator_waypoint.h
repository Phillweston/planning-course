#ifndef _TRAJECTORY_GENERATOR_WAYPOINT_H_
#define _TRAJECTORY_GENERATOR_WAYPOINT_H_

#include <Eigen/Eigen>
#include <vector>

class TrajectoryGeneratorWaypoint {
private:
  double _qp_cost;
  Eigen::MatrixXd _Q;
  Eigen::VectorXd _Px, _Py, _Pz;
public:
  TrajectoryGeneratorWaypoint();

  ~TrajectoryGeneratorWaypoint();

  Eigen::MatrixXd PolyQPGeneration(
      const int order,
      const Eigen::MatrixXd &Path,
      const Eigen::MatrixXd &Vel,
      const Eigen::MatrixXd &Acc,
      const Eigen::VectorXd &Time);
  
  int Factorial(int x);

  Eigen::MatrixXd SolvebyOOQP(
      const int d_order,                    // the order of derivative
      const Eigen::MatrixXd &Path,          // waypoints coordinates (3d)
      const Eigen::MatrixXd &Vel,           // boundary velocity
      const Eigen::MatrixXd &Acc,           // boundary acceleration
      const Eigen::VectorXd &Time);

  void GenStartConstraint(
      const int n_seq, 
      const int d_order, 
      const Eigen::VectorXd &Time, 
      const int order_deri, 
      Eigen::MatrixXd& Aeq_start,
      int *p_row_idx_A,
      int *irowA,
      int *jcolA,
      double *dA,
      int *p_k_A);

  void GenEndConstraint(
      const int n_seq, 
      const int d_order, 
      const Eigen::VectorXd &Time, 
      const int order_deri, 
      Eigen::MatrixXd& Aeq_end,
      int *p_row_idx_A,
      int *irowA,
      int *jcolA,
      double *dA,
      int *p_k_A);
  
  void GenWPConstraint(
      const int n_seq, 
      const int d_order, 
      const Eigen::VectorXd &Time, 
      const int order_deri,
      const Eigen::VectorXd& Path, 
      Eigen::MatrixXd& Aeq_wp,
      Eigen::VectorXd& beq_wp,
      int *p_row_idx_A,
      int *irowA,
      int *jcolA,
      double *dA,
      int *p_k_A);
  
  void GenContinuityConstraint(
      const int n_seq, 
      const int d_order, 
      const Eigen::VectorXd &Time, 
      const int order_deri, 
      Eigen::MatrixXd& Aeq_con,
      int *p_row_idx_A,
      int *irowA,
      int *jcolA,
      double *dA,
      int *p_k_A);

  void AddtodA(
      const double value, 
      const int irow,
      const int jcol,
      const int row_idx_A,
      int *irowA,
      int *jcolA,
      double *dA,
      int *p_k_A);

    int GetnnzA(const int n_seq, const int d_order);


};
        

#endif
