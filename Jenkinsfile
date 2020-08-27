pipeline {
    agent {label 'testnode'}
    stages {
        stage('Checkout') {
            steps {
                echo 'Checkout'
            }
        }
        stage('test shell') {
            steps {
                echo ' Shell'
		sh label: '', script: '''cd /home/autowise/OPENMP_consumerproducer/abc
bash test.sh'''
            }
        }
    }
}
