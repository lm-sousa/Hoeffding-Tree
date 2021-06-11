import sklearn_json as skj

from sklearn.datasets import load_iris
from sklearn import tree
import graphviz
import numpy

from dtreeviz.trees import *


def main():
    print("Hello World!")

    iris = load_iris()
    """
    X, y = iris.data, iris.target
    clf = tree.DecisionTreeClassifier()
    clf = clf.fit(X, y)

    dot_data = tree.export_graphviz(clf, out_file=None)
    graph = graphviz.Source(dot_data)
    graph.render("iris.dot")

    dot_data = tree.export_graphviz(clf, out_file=None,
                                    feature_names=iris.feature_names,
                                    class_names=iris.target_names,
                                    filled=True, rounded=True,
                                    special_characters=True)
    graph = graphviz.Source(dot_data)
    graph.render("iris_2.dot")

    skj.to_json(clf, "export.json")
    """

    clf = skj.from_json("visualisation/trial.json")

    dot_data = tree.export_graphviz(clf, out_file=None,
                                    feature_names=iris.feature_names,
                                    class_names=iris.target_names,
                                    filled=True, rounded=True,
                                    special_characters=True)
    graph = graphviz.Source(dot_data)
    graph.render("iris_json.dot")

    #print("Iris data: " + str(iris.target))

    #clf.fit(iris.data, iris.target)

    viz = dtreeviz(clf,
                   iris.data,
                   iris.target,
                   target_name='variety',
                   feature_names=iris.feature_names,
                   class_names=list(iris.target_names)
                   )

    viz.view()


if __name__ == "__main__":
    main()
