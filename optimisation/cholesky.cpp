#include <Eigen/Cholesky>

struct LM
{
    Eigen::VectorXd error(const Eigen::VectorXd& parameters, const Eigen::VectorXd& observation) const
    {
        Eigen::VectorXd error_(1);
        double x = parameters(0);
        double y = parameters(1);
        //Rosenbrock function f(x, y) = (1-x)^2 + 100(y-x^2)^2
        error_(0) = (1.0 - x) * (1.0 - x) + 100.0 * (y - x * x) * (y - x * x) - observation(0);
        return error_;
    }

    Eigen::MatrixXd jacobian(const Eigen::VectorXd& parameters) const
    {
        double x = parameters(0);
        double y = parameters(1);
        Eigen::MatrixXd jacobian_(1,2);
        jacobian_(0,0) = -2.0 * (1.0 - x) - 200.0 * (y - x * x) * 2.0 * x;
        jacobian_(0,1) = 200.0 * (y - x * x);
        return jacobian_;
    }

    Eigen::VectorXd solve(const Eigen::MatrixXd& jacobian, const Eigen::VectorXd& error, double lambda) const
    {
        Eigen::MatrixXd hessian;
        return damp(hessian=jacobian.transpose()*jacobian,lambda).llt().solve(-jacobian.transpose()*error);
    }

    Eigen::MatrixXd& damp(Eigen::MatrixXd& hessian, double lambda) const
    {
        assert(hessian.cols()==hessian.rows());
        for(int i = 0 ; i < hessian.cols() ; ++i)
            hessian(i,i) += lambda;
        return hessian;
    }

    void run(Eigen::VectorXd& parameters, const Eigen::VectorXd& observation, double lambda)
    {
        for(size_t i = 0 ; i < 10000 ; ++i)
        {
            Eigen::VectorXd errors = error(parameters,observation);
            double e1 = errors.squaredNorm();
            Eigen::VectorXd delta = solve(jacobian(parameters),errors,lambda);
            parameters += delta;
            double e2 = error(parameters,observation).squaredNorm();

            if (e2 < e1)
            {
               lambda /= 10.0;
            }
            else
            {
                lambda *= 10.0;
                parameters -= delta;
            }
            std::cout << "it(" << i << ") Lambda(" << lambda << ") e1(" << e1 << ") e2(" << e2 << ") X=(" << parameters.transpose() << ")" << std::endl;
        }
    }
};

void test()
{
    Eigen::VectorXd parameters(2);
    parameters(0) = 0.9;
    parameters(1) = 0.9;
    Eigen::VectorXd observations(1);
    observations(0) = 0;
    LM().run(parameters,observations,0.001);
}

