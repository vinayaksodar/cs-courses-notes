# CS229 notes

## Linear regression

### LMS algorithm

$$\theta := \theta + \alpha\sum^n_{i=1}(y^{(i)}-h_{\theta}(x^{(i)}))x^{(i)} $$

The above is batch gradient descent.

For stochatic gradient descent we simply update $\theta$ after every example.

$$\theta := \theta + \alpha(y^{(i)}-h_{\theta}(x^{(i)}))x^{(i)} $$

### Normal equations

For a closed form solution we dimply set the derivatives of the cost function to zero instead of an iterative minimization approach like LMS and obtain the normal equations.

Starting from:

$$
X^T X \theta = X^T \tilde{y}
$$

Thus, the value of $\theta$ that minimizes $J(\theta)$ is given in closed form by the equation:

$$
\theta = (X^T X)^{-1} X^T \tilde{y}
$$

---

> **Note**: In the above step, we are implicitly assuming that $X^T X$ is an invertible matrix.
>
> - If the number of linearly independent examples is fewer than the number of features, or if the features are not linearly independent, then $X^T X$ will not be invertible.
> - Even in such cases, it is possible to “fix” the situation with additional techniques, which we skip here for simplicity.

### Probabilistic Interpretation

There are two schools of thought: the **Frequentist approach** and the **Bayesian approach**.

---

#### Frequentist Approach

- Parameters ($\theta$) are treated as **fixed but unknown constants**.
- We use **Maximum Likelihood Estimation (MLE)** to find point estimates of parameters.
- We talk about **standard error**, not standard deviation, when parameters are point estimates.

> **Standard error** is the standard deviation of the estimated parameter across different datasets.

The assumed model is:

$$
y^{(i)} = \theta^T x^{(i)} + \varepsilon, \quad \varepsilon \sim \mathcal{N}(0, \sigma^2)
$$

i.e. $p(y|x;θ) = \mathcal{N}(\theta^Tx, \sigma^2) $

---

#### Bayesian Approach

- Parameters ($\theta$) are treated as **random variables** with prior distributions.
- Learning is done using **Bayes’ theorem**:

$$
p(\theta \mid D) \propto p(D \mid \theta) \, p(\theta)
$$

- Instead of a single point estimate, we obtain a **posterior distribution** over parameters.
- This allows us to quantify **uncertainty in $\theta$** more explicitly.

The model form is the same:

$$
y^{(i)} = \theta^T x^{(i)} + \varepsilon, \quad \varepsilon \sim \mathcal{N}(0, \sigma^2)
$$

In this course we mostly stop at MLE and subscribe to the frequentist approach

### Parametric vs Non-Parametric Learning

**Locally Weighted Linear Regression (LWLR)** is the first example we encounter of a **non-parametric algorithm**.

- The standard (unweighted) **linear regression** is a **parametric learning algorithm** because:

  - It has a fixed, finite number of parameters ($\theta_i$) that are fit to the data.
  - Once we’ve estimated $\theta_i$ and stored them, we no longer need to keep the training data around to make future predictions.

- In contrast, to make predictions using **locally weighted linear regression**:
  - We need to keep the **entire training set** around.
  - The prediction at a new point depends on re-weighting the training examples relative to that query.

---

The term **“non-parametric”** (roughly) refers to the fact that the **amount of information we must retain to represent the hypothesis $h$** grows **linearly with the size of the training set**.

## Logistic Regression

### Binary classification

We assume that the target variable $y^{(i)} \in \{0,1\}$ follows a **Bernoulli distribution** whose parameter p depends on the input $x^{(i)}$:

$$
 p(y | x; θ) =  \text{Bernoulli}(p^{(i)})
$$

with

$$
p^{(i)} = P(y^{(i)} = 1 \mid x^{(i)}; \theta) = \sigma(\theta^T x^{(i)})
$$

where $\sigma(z) = \frac{1}{1 + e^{-z}}$ is the **sigmoid function**. We use this as our hypothesis function $h_{\theta}(x)$.

Other functions that smoothly
increase from 0 to 1 can also be used, but for a couple of reasons that we’ll see
later (when we talk about GLMs, and when we talk about generative learning
algorithms), the choice of the logistic(sigmoid) function is a fairly natural one.

---

### Interpretation

- **Model form:** Bernoulli likelihood for binary outputs.
- **Parameters:** $\theta$ (weights) determine the probability via the sigmoid mapping.
- **Log-likelihood:**

$$
\ell(\theta) = \sum_{i=1}^m \Big( y^{(i)} \log p^{(i)} + (1-y^{(i)}) \log (1-p^{(i)}) \Big)
$$

This is what we maximize when training logistic regression (via MLE).

We get the stochatic gradient descent formula

$$\theta := \theta + \alpha(y^{(i)}-h_{\theta}(x^{(i)}))x^{(i)} $$

Notice the above is the same as the formula for linear regression the reason for this coincidence is clear when we study GLM.

### Multiclass Classification

In this case, $p(y \mid x; \theta)$ is a distribution over $k$ possible discrete outcomes and is thus a **multinomial distribution**.

Recall that a multinomial distribution involves $k$ numbers $\phi_1, \ldots, \phi_k$ specifying the probability of each of the outcomes, where:

$$
\sum_{i=1}^k \phi_i = 1
$$

We design a parameterized model that outputs $\phi_1, \ldots, \phi_k$ satisfying this constraint given the input $x$.

$$
P(y = i \mid x; \theta) = \phi_i
= \frac{\exp(t_i)}{\sum_{j=1}^k \exp(t_j)}
= \frac{\exp(\theta_i^T x)}{\sum_{j=1}^k \exp(\theta_j^T x)}
$$

---

#### Loss Function

The negative log-likelihood of the training data is:

$$
\ell(\theta) = \sum_{i=1}^n - \log \frac{\exp(\theta_{y^{(i)}}^T x^{(i)})}{\sum_{j=1}^k \exp(\theta_j^T x^{(i)})}
$$

---

#### Gradient of the Loss

The gradient of the loss with respect to the parameter vector $\theta_i$ is:

$$
\frac{\partial \ell(\theta)}{\partial \theta_i}
= \sum_{j=1}^n \big( \phi_i^{(j)} - 1\{y^{(j)} = i\} \big) \, x^{(j)}
$$

where

$$
\phi_i^{(j)} = \frac{\exp(\theta_i^T x^{(j)})}{\sum_{s=1}^k \exp(\theta_s^T x^{(j)})}
$$

is the probability that the model predicts class $i$ for example $x^{(j)}$.

---

With these gradients, one can implement **(stochastic) gradient descent** to minimize the loss function $\ell(\theta)$.

> We use bernouli to model binary classification and not binomial as we have only a single output if out output was a two dimensional vector one for each class it would be modeled using binomial which is just a special case of the multinomial.

### Newton’s Method

To get started, let’s consider Newton’s method for finding a zero of a function.  
Suppose we have some function $f: \mathbb{R} \to \mathbb{R}$, and we wish to find a value of $\theta$ such that:

$$
f(\theta) = 0
$$

where $\theta \in \mathbb{R}$ is a real number.

---

#### Update Rule (1D)

Newton’s method performs the following update:

$$
\theta := \theta - \frac{f(\theta)}{f'(\theta)}
$$

This has a natural interpretation:

- Approximate $f$ via a linear function that is **tangent** to $f$ at the current guess $\theta$.
- Solve for where that linear approximation equals zero.
- Let the next guess for $\theta$ be that solution.

---

#### Maximization via Newton’s Method

Newton’s method helps us solve equations of the form $f(\theta) = 0$.  
But what if we want to **maximize a function** $\ell(\theta)$?

- The maxima of $\ell$ correspond to points where $\ell'(\theta) = 0$.
- By setting $f(\theta) = \ell'(\theta)$, we obtain the Newton update for maximization/minimization:

$$
\theta := \theta - \frac{\ell'(\theta)}{\ell''(\theta)}
$$

---

#### Multidimensional Generalization

In logistic regression, $\theta$ is **vector-valued**, so we generalize Newton’s method to higher dimensions.  
This is also called the **Newton-Raphson method**:

$$
\theta := \theta - H^{-1} \nabla_\theta \ell(\theta)
$$

- $\nabla_\theta \ell(\theta)$ is the **gradient vector** (partial derivatives of $\ell(\theta)$ w.r.t. each $\theta_i$).
- $H$ is the **Hessian matrix**, a $(d+1) \times (d+1)$ matrix (including intercept), defined as:

$$
H_{ij} = \frac{\partial^2 \ell(\theta)}{\partial \theta_i \partial \theta_j}
$$

---

#### Efficiency Notes

- Newton’s method typically converges **faster** than batch gradient descent, requiring fewer iterations to get very close to the minimum.
- However, each iteration is more **computationally expensive**, since it requires computing and inverting the Hessian ($d \times d$ matrix).
- When applied to maximize the **log-likelihood in logistic regression**, this method is also known as **Fisher Scoring**.

## Generalized Linear Models (GLMs)

### The Exponential Family

A distribution belongs to the **exponential family** if it can be written in the form:

$$
p(y; \eta) = b(y) \exp\left(\eta^T T(y) - a(\eta)\right) \tag{3.1}
$$

- $\eta$: **natural (canonical) parameter**
- $T(y)$: **sufficient statistic** (often $T(y) = y$)
- $a(\eta)$: **log-partition function** (ensures normalization)
- $b(y)$: base measure

The term $e^{-a(\eta)}$ acts as a normalization constant ensuring the distribution integrates/sums to 1.

**Examples of exponential family distributions:**

- Gaussian (continuous data)
- Bernoulli (binary data)
- Multinomial (multiclass classification)
- Poisson (count data)
- Gamma and Exponential (continuous, non-negative random variables, e.g. time intervals)
- Beta and Dirichlet (distributions over probabilities)
- Many more…

---

### Constructing GLMs

Given input $x$ and output $y$, a GLM is defined by three assumptions/design choices:

1. **Distributional assumption:**

   $$
   y \mid x; \theta \sim \text{ExponentialFamily}(\eta)
   $$

2. **Prediction target:**  
   We predict the **expected value of $T(y)$ given $x$**:

   $$
   h_\theta(x) = E[y \mid x]
   $$

   (In most cases, $T(y) = y$. For logistic regression, $h_\theta(x) = P(y=1 \mid x; \theta) = E[y \mid x; \theta]$.)

3. **Linear relationship:**  
   The natural parameter $\eta$ is a linear function of $x$:
   $$
   \eta = \theta^T x
   $$
   (If $\eta$ is vector-valued, then $\eta_i = \theta_i^T x$.)

---

### Logistic Regression as a GLM

The **Bernoulli distribution** can be written as:

$$
p(y; \phi) = \phi^y (1-\phi)^{1-y}
= \exp\big( y \log \phi + (1-y) \log(1-\phi) \big)
$$

Rewriting in exponential family form:

$$
p(y; \phi) = \exp\big( \underbrace{\log \tfrac{\phi}{1-\phi}}_{\eta} \cdot y + \underbrace{\log(1-\phi)}_{-a(\eta)} \big)
$$

- Natural parameter:
  $$
  \eta = \log \frac{\phi}{1-\phi}
  $$
- Inverting gives:
  $$
  \phi = \frac{1}{1+e^{-\eta}}
  $$
  (the familiar **sigmoid function**).
- Sufficient statistic: $T(y) = y$
- Log-partition function: $a(\eta) = \log(1 + e^\eta)$
- Base measure: $b(y) = 1$

Thus, the Bernoulli distribution is in the **exponential family**.

---

### Hypothesis Function

Since $E[y \mid x; \theta] = \phi$, we obtain:

$$
h_\theta(x) = E[y \mid x; \theta]
= \frac{1}{1 + e^{-\eta}}
= \frac{1}{1 + e^{-\theta^T x}}
$$

So the logistic (sigmoid) function naturally arises as a **GLM with Bernoulli distribution**.

---

### Canonical Response and Link Functions

- **Canonical response function:**
  $$
  g(\eta) = E[T(y); \eta]
  $$
- **Canonical link function (inverse):**
  $$
  g^{-1}
  $$

Examples:

- Gaussian family → canonical response: **identity**
- Bernoulli family → canonical response: **logistic function**

The reason we **choose the exponential family** is that it gives us a very **general, mathematically convenient framework** for building learning algorithms.

---

#### 1. **Unifying Framework**

Many common distributions are members of the exponential family:

- Gaussian → Linear Regression
- Bernoulli → Logistic Regression
- Multinomial → Softmax Regression
- Poisson → Poisson Regression

So by restricting ourselves to exponential-family distributions, we get a **single recipe** (GLM) that can cover regression, classification, count models, etc.

---

#### 2. **Mathematical Convenience**

Exponential family distributions have very nice properties:

- The **log-likelihood** is **concave** in the natural parameter $\eta$ (good for optimization).
- Expectation and variance are tightly linked:

  $$
  E[T(y)] = a'(\eta), \quad \text{Var}(T(y)) = a''(\eta)
  $$

  (where $a(\eta)$ is the log-partition function).
  → This makes gradients and Hessians easy to compute.
- They guarantee a **normalization constant** is built-in via $a(\eta)$, so probability distributions are always valid.

---

#### 3. **Sufficient Statistics**

The form $p(y;\eta) = b(y) \exp(\eta^T T(y) - a(\eta))$ makes it explicit what the **sufficient statistic** $T(y)$ is.
This is crucial for efficient estimation: the entire dataset can often be summarized by simple aggregates (like sums, counts, or averages).

---

#### 4. **Link Functions Come for Free**

When we combine exponential-family likelihoods with the linearity assumption $\eta = \theta^T x$, the **canonical link functions** arise automatically:

- Gaussian → identity link
- Bernoulli → logistic (sigmoid) link
- Poisson → log link
  So instead of arbitrarily “inventing” a sigmoid for classification, it **falls out naturally** from the exponential-family structure.

---

#### 5. **Maximum Likelihood ↔ Convex Optimization**

With exponential-family distributions, the **negative log-likelihood** is a convex function in $\theta$.
That means:

- No bad local minima
- Standard optimization methods (Newton’s method, gradient descent, etc.) converge reliably.

---

We choose the exponential family because it is **broad enough** to cover the distributions we care about, but also **structured enough** to give us:

- simple sufficient statistics,
- automatic link functions,
- convex likelihoods,
- efficient optimization.

That’s why GLMs (built from exponential family assumptions) are both *general* and *practical*.

## Generative learning algorithms

### Discriminative vs. Generative Models

- **Discriminative models** directly learn the **posterior distribution**:

  $$
  P(Y \mid X)
  $$

  This is the probability of the label $Y$ given the input $X$. An example of a discriminative model is **logistic regression**.

- **Generative models** learn the **joint distribution** of $X$ and $Y$ by modeling:

  $$
  P(X \mid Y) \quad \text{and} \quad P(Y)
  $$

  Then, the posterior $P(Y \mid X)$ can be obtained using Bayes’ rule:

  $$
  P(Y \mid X) = \frac{P(X \mid Y) P(Y)}{P(X)}
  $$

> Note: Here x is also a random variable, even in bayesian we only assumed a distribution on weights not on x which was considered fixed.
---

#### Generative Models: Gaussian Discriminant Analysis

We assume $P(X \mid Y)$ is Gaussian, we can model each class-conditional distribution as:

$$
P(X \mid Y = y) = \mathcal{N}(X; \mu_y, \Sigma_y)
$$

- If we **assume a shared covariance matrix** $\Sigma$ across classes (i.e., $\Sigma_0 = \Sigma_1 = \Sigma$), the decision boundary is **linear**.

- If each class has its **own covariance matrix** $\Sigma_y$, the decision boundary becomes **quadratic**.

---

#### Decision Boundaries and Likelihood

GDA tries to **maximize the joint likelihood**:

$$
\mathcal{L}(\theta) = \prod_{i=1}^{m} P(x^{(i)} \mid y^{(i)}; \theta) P(y^{(i)}; \theta)
$$

Where $\theta$ includes $\mu_0, \mu_1, \Sigma$, and the class priors $\phi$ in the case of Bernoulli prior.

---

#### Logistic Regression vs. GDA

- GDA gives $P(Y \mid X)$ in **sigmoid form** when $P(X \mid Y)$ is Gaussian with shared covariance $\Sigma$:

  $$
  P(Y = 1 \mid X) = \frac{1}{1 + \exp(-\theta^T X)}
  $$

Where $\theta$ includes $\mu_0, \mu_1, \Sigma$, and the class priors.

- But GDA makes **strong assumptions** about the form of $P(X \mid Y)$. If these assumptions (e.g., Gaussian distribution) are **correct**, GDA performs better.

- If the assumptions are **incorrect**, then discriminative models like **logistic regression** can perform better, especially with a large dataset.

---

#### Rule of Thumb

- If you're **unsure** about the distribution of $P(X \mid Y)$, use **logistic regression**.
- If you have **strong prior knowledge** about $P(X \mid Y)$, a **generative model** (like GDA) may perform better.
- With a **large dataset**, logistic regression is often preferred due to fewer assumptions and better asymptotic behavior.

Convex optimization problem

An optimization problem is convex if:

The objective function is convex (for minimization problems),

The feasible set is convex (constraints define a convex region).

That’s why SVM’s trick is to avoid the non-convex ||w|| = 1 constraint and instead use convex inequalities $y^{(i)} (w^Tx^{(i)}) +b >=1$

## Kernels

Instead of calculating the inner product of **ϕ(xᵢ)** and **ϕ(xⱼ)** directly (where ϕ maps data to a higher-dimensional feature space), we use a kernel function **K(xᵢ, xⱼ)** such that:

$$
K(xᵢ, xⱼ) = \langle ϕ(xᵢ), ϕ(xⱼ) \rangle
$$

Ex.
$$
K(xᵢ, xⱼ) = \langle ϕ(xᵢ), ϕ(xⱼ) \rangle = \langle x_i, x_j \rangle ^ 2
$$

This allows us to **avoid explicitly computing the high-dimensional mapping** and by extension the innerproduct using the higher dimensional mapping, making computation efficient.

---

### When Can We Apply Kernels?

Kernels can only be used if the algorithm’s **learning rule or update rule** involves **inner products** of the input vectors.

#### **Example: LMS (Least Mean Squares)**

Original LMS weight update:

$$
w(t+1) = w(t) + η \big(d(t) - y(t)\big) x(t)
$$

where $y(t) = w(t)^\top x(t)$.

If we initialize $w(0) = 0$, after $T$ updates:

$$
w(T) = \sum_{i=1}^T α_i x(i), \quad \text{where } α_i = η \big(d(i) - y(i)\big)
$$

Then, the output for a new input $x$ is:

$$
y = w(T)^\top x = \sum_{i=1}^T α_i \big(x(i)^\top x\big)
$$

 Here, the prediction and learning rule depend only on **inner products** $x(i)^\top x$.
Thus, we can replace $x(i)^\top x$ with a kernel $K(x(i), x)$, giving:

$$
y = \sum_{i=1}^T α_i K(x(i), x)
$$

This is the **kernelized LMS**.

---

### Conditions for a Valid Kernel

- The **kernel matrix** $K$ (Gram matrix), where $K_{ij} = K(x_i, x_j)$, must be **positive semi-definite** (**Mercer’s condition**).

---

### Common Kernels

1. **Linear Kernel**

   $$
   K(x, z) = x^\top z
   $$

   Here, $ϕ(x) = x$ (no transformation).

2. **Polynomial Kernel**

   $$
   K(x, z) = (x^\top z + c)^d
   $$

3. **Gaussian (RBF) Kernel**

   $$
   K(x, z) = \exp\left(-\frac{\|x - z\|^2}{2σ^2}\right)
   $$

   The feature space is infinite-dimensional.

---

### Applications

The kernel trick applies to any algorithm where computations can be formulated to depend only on inner products, such as:

- **SVMs (Support Vector Machines)**
- **Kernel PCA**
- **Kernelized LMS**
- **Gaussian Processes**
- **Kernelized GLMs**

---

**Key Idea:**
By using kernels, we implicitly work in high-dimensional feature spaces without explicitly computing feature mappings.

## Support Vector Machine (SVM)

### **Goal**

Find a hyperplane that **maximizes the geometric margin** between positive and negative examples.
For linearly separable data, this is formulated as:

$$
\max_{\gamma, w, b} \; \gamma \quad
\text{s.t. } y^{(i)} (w^\top x^{(i)} + b) \ge \gamma, \; \|w\| = 1
$$

---

### **Primal Formulation**

We reformulate it into an equivalent convex optimization problem:

$$
\min_{w,b} \frac{1}{2} \|w\|^2
\quad \text{s.t. } y^{(i)} (w^\top x^{(i)} + b) \ge 1
$$

This minimizes the norm of $w$ while ensuring all points have a margin of at least 1.

---

### **Dual Formulation**

Using Lagrange multipliers and eliminating $w, b$, the problem becomes:

$$
\max_{\alpha} W(\alpha) =
\sum_{i=1}^n \alpha_i
- \frac{1}{2} \sum_{i,j=1}^n y^{(i)} y^{(j)} \alpha_i \alpha_j \langle x^{(i)}, x^{(j)} \rangle
$$

Subject to:

$$
\alpha_i \ge 0, \quad \sum_{i=1}^n \alpha_i y^{(i)} = 0
$$

The dual **depends only on inner products** $\langle x^{(i)}, x^{(j)} \rangle$.

---

### **Prediction**

Once we find the optimal $\alpha_i$, we can classify a new point $x$ as:

$$
f(x) = \sum_{i=1}^n \alpha_i y^{(i)} \langle x^{(i)}, x \rangle + b
$$

Only **support vectors** (points with $\alpha_i > 0$) contribute to the prediction.

---

### **Kernel Trick**

Since the dual involves **only inner products**, we can replace:

$$
\langle x^{(i)}, x^{(j)} \rangle \longrightarrow K(x^{(i)}, x^{(j)})
$$

where $K$ is a valid kernel function (e.g., linear, polynomial, Gaussian RBF).
This allows SVMs to operate in **high- or infinite-dimensional feature spaces without explicit mapping**.

---

**Key Insight:**

- SVM optimization in **dual form** enables the kernel trick.
- Kernels make SVM a powerful nonlinear classifier.
