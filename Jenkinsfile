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
		sh label: '', script: '''cd abc
bash test.sh'''
            }
        }
    }
}
