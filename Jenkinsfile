pipeline {
    agent {label 'testnode'}
    stages {
        stage('Checkout') {
            steps {
                echo 'Checkout'
		git branch: 'jenkinstest', credentialsId: '689e15b9-d92f-4e8c-8bc7-10c2c5de6133', url: 'https://github.com/fatalfake/OPENMP_consumerproducer.git'
            }
        }
        stage('test shell') {
            steps {
                echo ' Shell'
            }
        }
    }
}
